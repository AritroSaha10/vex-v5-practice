#pragma once
#include "main.h"

// Helper functions

void setDrive(int frontLeft, int backLeft, int frontRight, int backRight);

// Operator Control functions

// Values are of range [-127, 127]
void processArcadeDrive(int straight, int strafe, int yaw, double threshold = 0.05);