#include "main.h"

/*
MODES
0: tank: left stick controls left drive, right stick controls right drive,
1: arcade: left stick controls all drive
2: custom: left stick controls l/r, right stick controls f/b
*/
int drive_mode = 0;

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor left_drive(1);
pros::Motor right_drive(2, true);

pros::Motor left_lift(3, true);
pros::Motor right_lift(4);

pros::Motor left_intake(5);
pros::Motor right_intake(6, true);

void disabled() {}

void competition_initialize() {}

void autonomous() {
  left_drive.move(100);
  right_drive.move(100);
  pros::delay(250);
  left_drive.move(-100);
  right_drive.move(-100);
  pros::delay(250);
  left_drive.move(100);
  right_drive.move(100);
  pros::delay(250);
  left_drive.move(-100);
  right_drive.move(-100);
  pros::delay(250);
}

void opcontrol() {

  int left_motor_speed = 0;
  int right_motor_speed = 0;

  int lift_speed = 0;

  int intake_speed = 0;

  while(true) {

    // drive

    if (drive_mode == 0) {
      left_motor_speed = controller.get_analog(ANALOG_LEFT_Y);
      right_motor_speed = controller.get_analog(ANALOG_RIGHT_Y);
    } else if (drive_mode == 1) {
      int direction = controller.get_analog(ANALOG_LEFT_Y);
      left_motor_speed = (controller.get_analog(ANALOG_LEFT_Y) + direction) / 1.5;
      right_motor_speed = (controller.get_analog(ANALOG_LEFT_Y) - direction) / 1.5;
    } else if (drive_mode == 2) {
      int direction = controller.get_analog(ANALOG_LEFT_X);
      left_motor_speed = (controller.get_analog(ANALOG_RIGHT_Y) + direction) / 1.5;
      right_motor_speed = (controller.get_analog(ANALOG_RIGHT_Y) - direction) / 1.5;
    } else {
      controller.set_text(0, 0, "Unknown mode");
      while(true) {
        pros::delay(100);
      }
    }

    // lift

    if (controller.get_digital_new_press(DIGITAL_UP)) {
      if (lift_speed == 63) {
        lift_speed = 0;
      } else {
        lift_speed = 63;
      }
    }

    if (controller.get_digital_new_press(DIGITAL_DOWN)) {
      if (lift_speed == -63) {
        lift_speed = 0;
      } else {
        lift_speed = -63;
      }
    }

    // intake

    if (controller.get_digital_new_press(DIGITAL_X)) {
      if (intake_speed == 63) {
        intake_speed = 0;
      } else {
        intake_speed = 63;
      }
    }

    if (controller.get_digital_new_press(DIGITAL_B)) {
      if (intake_speed == -63) {
        intake_speed = 0;
      } else {
        intake_speed = -63;
      }
    }

    left_drive.move(left_motor_speed);
    right_drive.move(right_motor_speed);

    left_lift.move(lift_speed);
    right_lift.move(lift_speed);

    left_intake.move(intake_speed);
    right_intake.move(intake_speed);

    pros::delay(10);

  }
}
