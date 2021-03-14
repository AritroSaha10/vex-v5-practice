#include "main.h"
#include "tracking.h"

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

void tracking(void* param) {
    
}