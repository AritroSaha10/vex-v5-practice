#include "claw.h"
#include "globals.h"

// Range: [-12000, 12000]
void setClaw(int voltage) {
    claw.move_voltage(voltage);
}