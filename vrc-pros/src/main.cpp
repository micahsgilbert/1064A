#include "main.h"

// modes = 0: "TANK", 1: "ARCADE", 2: "CUSTOM"
int mode = 0;

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	pros::Motor left_drive(1);
  pros::Motor right_drive(2, true);

  while(true) {
    // get controller values

    int left_motor_speed = 0;
    int right_motor_speed = 0;

    if (mode == 0) {
      left_motor_speed = controller.get_analog(ANALOG_LEFT_Y);
      right_motor_speed = controller.get_analog(ANALOG_RIGHT_Y);

    } else if (mode == 1) {
      controller.set_text(0, 0, "ARCADE mode not implemented");
      while(true) {
        pros::delay(100);
      }
    } else if (mode == 2) {
      controller.set_text(0, 0, "CUSTOM mode not implemented");
      while(true) {
        pros::delay(100);
      }
    } else {
      controller.set_text(0, 0, "Unknown mode");
      while(true) {
        pros::delay(100);
      }
    }

    left_drive.move(left_motor_speed);
    right_drive.move(right_motor_speed);
  }
}
