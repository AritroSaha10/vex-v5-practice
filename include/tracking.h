#pragma once

class Vector2 {
    private:
        double x, y;
    public:
        Vector2();
        Vector2(const Vector2 &v1);
        Vector2(double x, double y);

        // Get functions
        double getX();
        double getY();

        // Calculation functions
        double getMagnitude(); // Gets magnitude / length of vector
        double getAngle(); // Gets angle of vector

        // Others
        void normalize();

        // Arithmetic
        friend Vector2 operator+ (const Vector2 &v1, const Vector2 &v2);
        friend Vector2 operator- (const Vector2 &v1, const Vector2 &v2);
        friend Vector2 operator* (const Vector2 &v1, const Vector2 &v2);
};

class TrackingData {
    private:
        Vector2 pos;
        double heading; // In radians
    public:
        TrackingData();
        TrackingData(Vector2 pos, double h);
        TrackingData(double x, double y, double h);

        // Get functions
        Vector2 getPos();
        double getHeading();

        // Update functions
        void update(Vector2 newPos, double newH);
        void update(double newX, double newY, double newH);
};

void tracking(void* param);