#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
#include "chassis.h"
#include "autons.h"

int auton = 0;
void on_center_button() {
    auton ++;
    auton %= 4;
}
void initialize() {
    // dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    // clawrotate.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    pros::lcd::register_btn1_cb(on_center_button);
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
    if (auton == 0) {
        Right();
    } else if (auton == 1) {
        Left();
    } else if (auton == 2) {
        AWP();
    } else if (auton == 3) {
        Skills();
    }
}

void opcontrol() {
    bool clawspinslow = false;
    bool toggleclaw = false;
    master.rumble(". - .-.-- -");


	while (true) {
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);

        // if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        //     clawspinslow = !clawspinslow;
        // }
        // if (clawspinslow) {
        //     clawspin.move_velocity(80);
        // } else {
        //     clawspin.move_velocity(0);
        // }

        // if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        //     dr4b.move_velocity(-150);
        // } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        //     dr4b.move_velocity(150);
        // } else {
        //     dr4b.move_velocity(0);
        // }

        // if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        //     clawrotate.move_velocity(50);
        // } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        //     clawrotate.move_velocity(-50);
        // } else {
        //     clawrotate.move_velocity(0);
        // }

        // if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        //     clawrotate.move_velocity(200);
        // } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        //     clawrotate.move_velocity(-200);
        // } else {
        //     clawrotate.move_velocity(0);}
        


		chassis.arcade(-turn, -forward);

        //delay
		pros::delay(20);
	}
}