#include "globals.h"
#include "chassis.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Motor for drivetrain
pros::Motor frontLeftDrive(FL_PORT);
pros::Motor backLeftDrive(BR_PORT);
pros::Motor frontRightDrive(FR_PORT);
pros::Motor backRightDrive(BR_PORT);

// Motor for arm
pros::Motor arm(ARM_PORT);

// Motor for claw
pros::Motor claw(CLAW_PORT);

// External encoders for tracking distance
pros::ADIEncoder leftEncoder(LEFT_ENCODER_1, LEFT_ENCODER_2);
pros::ADIEncoder rightEncoder(RIGHT_ENCODER_1, RIGHT_ENCODER_2);
pros::ADIEncoder backEncoder(BACK_ENCODER_1, BACK_ENCODER_2);

// Tracking data from odom
TrackingData trackingData;