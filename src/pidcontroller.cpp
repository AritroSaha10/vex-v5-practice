#include "pidcontroller.h"
#include "globals.h"
#include "main.h"

// Unit is milliseconds
#define SETTLE_DELAY 200 

// Initialize with defaults
PIDInfo::PIDInfo() {
    this->p = 1;
    this->i = 1;
    this->d = 1;
}

// Initialize with params
PIDInfo::PIDInfo(double p, double i, double d) {
    this->p = p;
    this->i = i;
    this->d = d;
}

PIDController::PIDController(double target, double tolerance, PIDInfo constants) {
    this->target = target;
    this->tolerance = tolerance;
    this->constants = constants;
}

double PIDController::step(double sensorVal) {
    // Set current to sensorVal
    this->current = sensorVal;

    // Get new error
    this->error = this->target - this->current;

    // Add error to integral since its the sum of all errors
    this->integral += this->error;

    // Get the derivative by getting rate of change
    this->derivative = this->error - this->lastError;

    // Disable integrals until it comes into usable range
    if (this->error == 0) this->integral = 0;
    if (abs(this->error) > (127 / 2)) this->integral = 0;

    // Run the calculation
    this->speed = (this->constants.p * this->error) + (this->constants.i * this->integral) + (this->constants.d * this->derivative);

    // Robot likely stopped if two previous errors were under tolerance
    if (abs(this->error) <= this->tolerance && abs(this->lastError) <= this->tolerance) { 
        // Stop for a specific amount of time before being completely settled, should ensure that we are in exact position we want to be in
        if (!this->settling) {
            this->settleStart = pros::millis();
            this->settling = true;
        }

        // We shouldn't be moving at all until the settle time stops
        this->speed = 0;
        
        if (pros::millis() - this->settleStart > SETTLE_DELAY) {
            // Waited long enough, we can finally settle
            this->settled = true;
        }
    } else {
        // Don't settle
        this->settling = false;
        this->settled = false;
    }

    // Set last error to current error for next iter
    this->lastError = this->error;

    return this->speed;
}

void PIDController::reset() {
    this->current = 0;
    this->error = 0;
    this->lastError = 0;
    this->integral = 0;
    this->derivative = 0;
    this->target = 0;
    this->speed = 0;

    this->settleStart = 0;
    this->settling = true;
    this->settled = true;
}

bool PIDController::isSettled() {
    return this->settled;
}