#include "main.h"

// modes = "TANK", "ARCADE", "CUSTOM"
char mode[] = "TANK";

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
	pros::Motor left_drive(1);
  pros::Motor right_drive(1, true);

  while(true) {
    // get controller values

    int leftMotorSpeed;
    int rightMotorSpeed;

    if (mode == "TANK") {
      leftMotorSpeed = controller.get_analog(ANALOG_LEFT_Y);
      rightMotorSpeed = controller.get_analog(ANALOG_RIGHT_Y);

    } else if (mode == "ARCADE") {
      controller.set_text(0, 0, "ARCADE mode not implemented");
    } else if (mode == "CUSTOM") {
      controller.set_text(0, 0, "CUSTOM mode not implemented");
    } else {
      controller.set_text(0, 0, "Unknown mode");
    }
  }
}
