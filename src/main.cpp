#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup leftdrive({1, 2}, pros::MotorGearset::green);
pros::MotorGroup rightdrive({3, 4}, pros::MotorGearset::green);
pros::Imu imu(5);
lemlib::Drivetrain drivetrain(&leftdrive, &rightdrive, 10, lemlib::Omniwheel::NEW_325, 360, 2.0);
pros::Rotation horizontalencoder(6);
pros::Rotation verticalencoder(7);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalencoder, lemlib::Omniwheel::NEW_2, -5.75);
lemlib::TrackingWheel vertical_tracking_wheel(&verticalencoder, lemlib::Omniwheel::NEW_2, -2.5);
lemlib::OdomSensors sensors(&vertical_tracking_wheel,
                            nullptr,
                            &horizontal_tracking_wheel,
                            nullptr,
                            &imu
);
lemlib::ControllerSettings angularcontroller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
lemlib::ControllerSettings lateralcontroller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, lateralcontroller, angularcontroller, sensors);
void initialize() {
	rightdrive.set_reversed(true);
	pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
}

void opcontrol() {
	while (true) {
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);


		chassis.arcade(forward, turn);
		pros::delay(20);
	}
}