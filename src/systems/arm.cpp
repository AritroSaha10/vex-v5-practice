#include "arm.h"
#include "globals.h"

// Range: [-12000, 12000]
void setArm(int voltage) {
    arm.move_voltage(voltage);
}