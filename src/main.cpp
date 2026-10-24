#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup leftdrive({1, -2}, pros::MotorGearset::green);
pros::MotorGroup rightdrive({-3, 4}, pros::MotorGearset::green);
pros::Imu imu(5);
// pros::Motor intake(8, pros::MotorGearset::green);
pros::MotorGroup dr4b({-6, 7}, pros::MotorGearset::green);
pros::Motor clawrotate(8, pros::MotorGearset::green);
pros::Motor clawspin(-9, pros::MotorGearset::green);
lemlib::Drivetrain drivetrain(&leftdrive, &rightdrive, 12, lemlib::Omniwheel::NEW_325, 360, 2.0);
lemlib::TrackingWheel left_tracking_wheel(&leftdrive, lemlib::Omniwheel::NEW_325, -6, 360);
lemlib::TrackingWheel right_tracking_wheel(&rightdrive, lemlib::Omniwheel::NEW_325, 6, 360);
lemlib::OdomSensors sensors(&left_tracking_wheel,
                            &right_tracking_wheel,
                            nullptr,
                            nullptr,
                            &imu);

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
    dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
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
    bool intakeon = false;
    master.rumble(".  - .-.-- -");
	while (true) {
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            intakeon = !intakeon;
        }
        if (intakeon) {
            clawspin.move_velocity(200);
        } else {
            clawspin.move_velocity(0);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            dr4b.move_velocity(-150);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            dr4b.move_velocity(150);
        } else {
            dr4b.move_velocity(0);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            clawrotate.move_velocity(100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            clawrotate.move_velocity(-100);
        } else {
            clawrotate.move_velocity(0);
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            clawrotate.move_velocity(200);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            clawrotate.move_velocity(-200);} else {
            clawrotate.move_velocity(0);}
        
		chassis.arcade(forward, turn);
		pros::delay(20);
	}
}