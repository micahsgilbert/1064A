#include "main.h"


void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_drive(1);
  pros::Motor right_drive(1, true);

  while(true) {
    left_drive.move(127);
    right_drive.move(127);

    pros::delay(2000);

    left_drive.move(0);
    right_drive.move(0);

    pros::delay(2000);

    left_drive.move(-127);
    right_drive.move(-127);

    pros::delay(2000);

    left_drive.move(0);
    right_drive.move(0);

    pros::delay(2000);
  }
}
