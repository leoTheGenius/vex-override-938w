#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor frontleft(1, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor frontright(10, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor backleft(2, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor backright(9, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

void initialize() {
	frontright.set_reversed(true);
	backright.set_reversed(true);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while (true) {
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);

		int leftp = forward - turn;
		int rightp = forward + turn;

		frontleft.move(leftp);
		backleft.move(leftp);
		frontright.move(rightp);
		backright.move(rightp);

		pros::delay(20);
	}
}