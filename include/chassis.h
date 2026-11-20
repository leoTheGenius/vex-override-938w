#pragma once

#include "main.h"
#include "lemlib/api.hpp"

// Controller
inline pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drivetrain Motors
inline pros::MotorGroup leftdrive({-7, -10, -6}, pros::MotorGearset::green);
inline pros::MotorGroup rightdrive({-2, -9, -5}, pros::MotorGearset::green);

// Sensors
inline pros::Imu imu(14);
inline pros::Rotation vertencoder(12);
inline pros::Rotation horizencoder(11);

// Subsystems (Uncomment when ready to use)
// inline pros::Motor intake(8, pros::MotorGearset::green);
// inline pros::MotorGroup dr4b({-18, 9}, pros::MotorGearset::green);
// inline pros::Motor clawrotate(20, pros::MotorGearset::green);
// inline pros::Motor clawspin(-21, pros::MotorGearset::green);

// LemLib Drivetrain & Tracking Wheels
inline lemlib::Drivetrain drivetrain(
    &leftdrive,                   // left motor group
    &rightdrive,                  // right motor group
    12,                           // 12 inch track width
    lemlib::Omniwheel::NEW_325,   // using new 3.25" omnis
    450,                          // drivetrain rpm is 450
    2.0                           // horizontal drift is 2
);

inline lemlib::TrackingWheel vertical_tracking_wheel(
    &vertencoder,                 // vertical rotation sensor
    lemlib::Omniwheel::NEW_2,     // using new 2" omnis
    -6,                           // -6" offset from tracking center
    1                             // 1:1 gear ratio
);

inline lemlib::TrackingWheel horizontal_tracking_wheel(
    &horizencoder,                // horizontal rotation sensor
    lemlib::Omniwheel::NEW_2,     // using new 2" omnis
    6,                            // 6" offset from tracking center
    1                             // 1:1 gear ratio
);

// Odometry Sensors
inline lemlib::OdomSensors sensors(
    &vertical_tracking_wheel,     // vertical tracking wheel 1
    nullptr,                      // vertical tracking wheel 2 (none)
    &horizontal_tracking_wheel,   // horizontal tracking wheel 1
    nullptr,                      // horizontal tracking wheel 2 (none)
    &imu                          // inertial sensor
);

// Angular PID Controller
inline lemlib::ControllerSettings angularcontroller(
    2,    // proportional gain (kP)
    0,    // integral gain (kI)
    10,   // derivative gain (kD)
    3,    // anti windup
    1,    // small error range, in degrees
    100,  // small error range timeout, in milliseconds
    3,    // large error range, in degrees
    500,  // large error range timeout, in milliseconds
    0     // maximum acceleration (slew)
);

// Lateral PID Controller
inline lemlib::ControllerSettings lateralcontroller(
    10,   // proportional gain (kP)
    0,    // integral gain (kI)
    3,    // derivative gain (kD)
    3,    // anti windup
    1,    // small error range, in inches
    100,  // small error range timeout, in milliseconds
    3,    // large error range, in inches
    500,  // large error range timeout, in milliseconds
    20    // maximum acceleration (slew)
);

// LemLib Chassis Object
inline lemlib::Chassis chassis(drivetrain, lateralcontroller, angularcontroller, sensors);
