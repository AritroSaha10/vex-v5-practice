#pragma once
#include "tracking.h"

/* 
 * Stores PID constants, such as Proportional, Integral, Derivative weights 
*/
typedef struct PIDInfo {
    double p;
    double i;
    double d;

    PIDInfo(double p, double i, double d);
    PIDInfo();
} PIDInfo;

class PIDController {
    private:
        double current;
        double error, lastError;
        double integral, derivative;
        double target;
        double speed;

        double settleStart;
        bool settling, settled;

        double tolerance;
        PIDInfo constants;
    public:
        PIDController(double target, double tolerance, PIDInfo constants);
        
        double step(double sensorVal); // Returns speed

        void setTarget(double newTarget); // Set new target
        void reset(); // Reset all values

        bool isSettled();
};

void strafe(Vector2 dir, double turn);
void turnToAngle(double target); // Target is in degrees