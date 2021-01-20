#include "main.h"

// Motors for drivetrain
extern pros::Motor frontLeftDrive;
extern pros::Motor backLeftDrive;
extern pros::Motor frontRightDrive;
extern pros::Motor backRightDrive;

// Motor for arm
extern pros::Motor arm;

// Motor for claw
extern pros::Motor claw;

// External encoders for tracking distance
extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;
extern pros::ADIEncoder middleEncoder;