#include "main.h"
#include "systems/drive.h"
#include "globals.h"

void myOpControl() {
    while (true) {
        // Get inputs
        int leftX = master.get_analog(ANALOG_LEFT_X); // Strafe movement input, range: [-127, 127]
        int leftY = master.get_analog(ANALOG_LEFT_Y); // Straight movement input, range: [-127, 127]
        int rightX = master.get_analog(ANALOG_RIGHT_X); // Rotation input, range: [-127, 127]

        // Process arcade drive
        processArcadeDrive(leftY, leftX, rightX);

        // Diagnostics
        pros::delay(15);
    }
}