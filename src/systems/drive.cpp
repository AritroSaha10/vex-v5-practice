#include "drive.h"
#include "globals.h"

void setDrive(int frontLeft, int backLeft, int frontRight, int backRight) {
    frontLeftDrive.move(frontLeft);
    backLeftDrive.move(backLeft);
    frontRightDrive.move(frontRight);
    backRightDrive.move(backRight);
}

// Values are of range [-127, 127]
void processArcadeDrive(int straight, int strafe, int yaw, double threshold = 0.05) {
    // Max voltage in millivolts
    const int maxVoltage = 12000;

    // Set values to zero if threshold is not crossed to remove erroneous input
    straight = (double) abs(straight) <= threshold ? 0 : straight;
    strafe = (double) abs(strafe) <= threshold ? 0 : strafe;
    yaw = (double) abs(yaw) <= threshold ? 0 : yaw;

    // Divide the value by 127 to get a range of [-1.0, 1.0], obtain power of 3 for acceleration curve, and clamp it from -1 to 1
    double straightScaled = std::clamp(pow(straight / 127.0, 3.0), -1.0, 1.0); 
    double strafeScaled   = std::clamp(pow(strafe / 127.0, 3.0), -1.0, 1.0);
    double yawScaled      = std::clamp(pow(yaw / 127.0, 3.0), -1.0, 1.0); 

    // X-Drive math for movement
    int speedFL = (int) (std::clamp(straightScaled + strafeScaled + yawScaled, -1.0, 1.0) * maxVoltage);
    int speedBL = (int) (std::clamp(straightScaled - strafeScaled + yawScaled, -1.0, 1.0) * maxVoltage);
    int speedFR = (int) (std::clamp(straightScaled - strafeScaled - yawScaled, -1.0, 1.0) * maxVoltage);
    int speedBR = (int) (std::clamp(straightScaled + strafeScaled - yawScaled, -1.0, 1.0) * maxVoltage);  

    setDrive(speedFL, speedBL, speedFR, speedBR);
}

