#include "main.h"
#include "systems/drive.h"
#include "systems/arm.h"
#include "systems/claw.h"
#include "globals.h"

void myOpControl() {
    while (true) {
        #pragma region Movement
        // Get inputs
        int leftX = master.get_analog(ANALOG_LEFT_X); // Strafe movement input, range: [-127, 127]
        int leftY = master.get_analog(ANALOG_LEFT_Y); // Straight movement input, range: [-127, 127]
        int rightX = master.get_analog(ANALOG_RIGHT_X); // Rotation input, range: [-127, 127]

        // Process arcade drive
        processArcadeDrive(leftY, leftX, rightX);
        #pragma endregion

        #pragma region Arm
        int armVoltage = 0;

        // Subtract 12000 from armVoltage if L2 is held down, and add 12000 if R2 is held down
        // Goes back to 0 if both held down
        armVoltage = master.get_digital(DIGITAL_L2) != 0 ? armVoltage - 12000 : armVoltage;
        armVoltage = master.get_digital(DIGITAL_R2) != 0 ? armVoltage + 12000 : armVoltage;

        setArm(armVoltage);
        #pragma endregion

        #pragma region Claw
        int clawVoltage = 0;

        // Subtract 12000 from clawVoltage if L2 is held down, and add 12000 if R2 is held down
        // Goes back to 0 if both held down
        clawVoltage = master.get_digital(DIGITAL_L1) != 0 ? clawVoltage - 12000 : clawVoltage;
        clawVoltage = master.get_digital(DIGITAL_R1) != 0 ? clawVoltage + 12000 : clawVoltage;

        setClaw(clawVoltage);
        #pragma endregion
        
        // Diagnostics
        pros::delay(15);
    }
}