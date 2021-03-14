#include "main.h"
#include "chassis.h"
#include "tracking.h"
#include "globals.h"

// No param initializer
Vector2::Vector2() {
    this->x = 0.0;
    this->y = 0.0;
}

// Copy initializer
Vector2::Vector2(const Vector2 &v1) {
    this->x = v1.x;
    this->y = v1.y;
}

// Value initializer
Vector2::Vector2(double x, double y) {
    this->x = x;
    this->y = y;
}

// Get x
double Vector2::getX() {
    return this->x;
}

// Get y
double Vector2::getY() {
    return this->y;
}

// Get the magnitude / length of a vector
double Vector2::getMagnitude() {
    return sqrt(this->x * this->x + this->y * this->y);
}

// Get angle of vector
double Vector2::getAngle() {
    return atan2(this->y, this->x);
}

// Normalize the vector
void Vector2::normalize() {
    double magnitude = this->getMagnitude();

    this->x /= magnitude;
    this->y /= magnitude;
}

// Add two vectors
Vector2 operator+ (const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

// Subtract two vectors
Vector2 operator- (const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

// Multiply two vectors
Vector2 operator* (const Vector2 &v1, const Vector2 &v2) {
    return Vector2(v1.x * v2.x, v1.y * v2.y);
}


// No param initializer
TrackingData::TrackingData() {
    this->pos = Vector2(0, 0);
    this->heading = 0.0;
}

// Vec2 + header initializer
TrackingData::TrackingData(Vector2 pos, double h) {
    this->pos = pos;
    this->heading = h;
}

// All values initializer
TrackingData::TrackingData(double x, double y, double h) {
    this->pos = Vector2(x, y);
    this->heading = h;
}

// Get pos
Vector2 TrackingData::getPos() {
    return this->pos;
}

// Get heading
double TrackingData::getHeading() {
    return this->heading;
}

// Update using vec and heading
void TrackingData::update(Vector2 newPos, double newH) {
    this->pos = newPos;
    this->heading = newH;
}

// Update using all values
void TrackingData::update(double newX, double newY, double newH) {
    this->pos = Vector2(newX, newY);
    this->heading = newH;
}

// Encoder deltas
double lDelta; // Delta of distance travelled by left tracking wheel
double rDelta; // Delta of distance travelled by right tracking wheel
double bDelta; // Delta of distance travelled by back tracking wheel

// Real world distances
double lDist; // lDelta in inches
double rDist; // rDelta in inches
double bDist; // bDelta in inches
double aDelta; // Delta of angle in radians

// Previous encoder values
double lLast; // Last value of left tracking wheel
double rLast; // Last value of right tracking wheel
double bLast; // Last value of back tracking wheel

// Constants and macros
const double lrOffset = WHEELBASE / 2.0f; // Offset of the left / right tracking wheel from the center in terms of x axis
const double bOffset = -BACK_WHEEL_OFFSET; // Offset of the back tracking wheel from the center in terms of y axis (negative because its in the back)

// Conversion calculations
#define DRIVE_DEGREE_TO_INCH (PI * DRIVE_WHEEL_DIAMETER / 360) 
#define TRACKING_WHEEL_DEGREE_TO_INCH (PI * TRACKING_WHEEL_DIAMETER / 360)

void tracking(void* param) {
    // Initialize variables
    lLast = 0; // Last encoder value of left
    rLast = 0; // Last encoder value of right
    bLast = 0; // Last encoder value of back

    double left = 0; // Total distance travelled by left tracking wheel
    double right = 0; // Total distance travelled by right tracking wheel
    double lateral = 0; // Total distance travelled laterally (measured from back tracking wheel)
    double angle = 0; // Current arc angle

    // Reset encoders to 0 before starting
    leftEncoder.reset();
    rightEncoder.reset();
    backEncoder.reset();

    // Tracking loop, follows this: http://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf
    while (true) {
        Vector2 localPos;

        // Get encoder data
        double lEncVal = leftEncoder.get_value();
        double rEncVal = rightEncoder.get_value();
        double bEncVal = backEncoder.get_value();

        // Calculate delta values
        lDelta = lEncVal - lLast;
        rDelta = rEncVal - rLast;
        bDelta = bEncVal - bLast;

        // Calculate IRL distances from deltas
        lDist = lDelta * TRACKING_WHEEL_DEGREE_TO_INCH;
        rDist = rDelta * TRACKING_WHEEL_DEGREE_TO_INCH;
        bDist = bDelta * TRACKING_WHEEL_DEGREE_TO_INCH;

        // Update last values for next iter since we don't need to use last values for this iteration
        lLast = lEncVal;
        rLast = rEncVal;
        bLast = bEncVal;

        // Update total distance vars
        left += lEncVal;
        right += rEncVal;
        lateral += bEncVal;

        // Calculate new absolute orientation
        double prevAngle = angle; // Previous angle, used for delta
        angle = (left - right) / (lrOffset * 2.0f);

        // Get angle delta
        aDelta = angle - prevAngle;

        // Calculate using different formulas based on if orientation change
        double avgLRDelta = (lDist + rDist) / 2; // Average of delta distance travelled by left and right wheels
        if (aDelta == 0.0f) {
            // Set the local positions to the distances travelled since the angle didn't change
            localPos = Vector2(bDist, avgLRDelta);
        } else {
            // Use the angle to calculate the local position since angle did change
            localPos = Vector2(
                2 * sin(angle / 2) * (bDist / aDelta + bOffset),
                2 * sin(angle / 2) * (avgLRDelta / aDelta + lrOffset)
            );
        }

        // Calculate the average orientation
        double avgAngle = prevAngle + aDelta / 2;

        // Calculate global offset https://www.mathsisfun.com/polar-cartesian-coordinates.html
        double globalOffsetX = cos(avgAngle); // cos(θ) = x (i think)
        double globalOffsetY = sin(avgAngle); // sin(θ) = y (i think)

        // Finally, update the global position
        Vector2 globalPosChange(
            (localPos.getY() * globalOffsetX) + (localPos.getX() * globalOffsetX),
            (localPos.getY() * globalOffsetX) - (localPos.getX() * globalOffsetY)
        );

        // Update tracking data
        trackingData.update(
            trackingData.getPos() + globalPosChange,
            angle
        );

        // Debug print (can't use display so just throw to serial)
        printf("X: %f, Y: %f, A: %f", 
                trackingData.getPos().getX(), 
                trackingData.getPos().getY(), 
                trackingData.getHeading() * 180 / PI);
        
        pros::delay(5);
    }   
}