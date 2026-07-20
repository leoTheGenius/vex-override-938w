#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor front_left(1, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor front_right(10, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor back_left(2, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor back_right(9, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

void initialize() {
	front_right.set_reversed(true);
	back_right.set_reversed(true);
	pros::screen::print(TEXT_MEDIUM, 1, "Arcade Drive Ready");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while (true) {
		int forward = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);

		int left_power = forward - turn;
		int right_power = forward + turn;

		front_left.move(left_power);
		back_left.move(left_power);
		front_right.move(right_power);
		back_right.move(right_power);

		pros::delay(20);
	}
}