#include "main.h"
#include "config.h"
#include "motors.h"
#include "auton.h"
#include "auton_skills.h"

/*
CONTROLS
left & right sticks control drive as configured
up/down buttons control lift. each button toggles between its direction and off
x/b buttons control intake, same way as lift
*/

pros::Controller controller(pros::E_CONTROLLER_MASTER);

void disabled() {
  motors::left_drive.move(0);
  motors::right_drive.move(0);
  motors::left_lift.move(0);
  motors::right_lift.move(0);
  motors::left_intake.move(0);
  motors::right_intake.move(0);
}

void competition_initialize() {}

void initialize() {
  pros::lcd::initialize();
  motors::left_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  motors::right_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void autonomous() {
  auton(0);
}

void write_debug_to_screen() {
  pros::lcd::print(0,"Lift Velocities:  L: %i R: %i",(int)motors::left_lift.get_actual_velocity(),(int)motors::right_lift.get_actual_velocity());
}

void opcontrol() {

  int left_motor_speed = 0;
  int right_motor_speed = 0;

  int lift_mult = 0;
  int intake_mult = 0;

  uint32_t iter = 0;

  while(true) {

    // drive

    if (config::drive_mode == 0) {
      left_motor_speed = controller.get_analog(ANALOG_LEFT_Y);
      right_motor_speed = controller.get_analog(ANALOG_RIGHT_Y);
    } else if (config::drive_mode == 1) {
      int direction = controller.get_analog(ANALOG_LEFT_Y);
      left_motor_speed = (controller.get_analog(ANALOG_LEFT_Y) + direction) / 1.5;
      right_motor_speed = (controller.get_analog(ANALOG_LEFT_Y) - direction) / 1.5;
    } else if (config::drive_mode == 2) {
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

    if (controller.get_digital_new_press(DIGITAL_R1)) {
      if (lift_mult < 2) {
        lift_mult++;
      }
    }

    if (controller.get_digital_new_press(DIGITAL_R2)) {
      if (lift_mult > -2) {
        lift_mult--;
      }
    }

    if (controller.get_digital_new_press(DIGITAL_LEFT)) {
      lift_mult = 0;
    }

    // intake

    if (controller.get_digital_new_press(DIGITAL_UP)) {
      if (intake_mult == 1) {
        intake_mult = 0;
      } else {
        intake_mult = 1;
      }
    }

    if (controller.get_digital_new_press(DIGITAL_DOWN)) {
      if (intake_mult == -1) {
        intake_mult = 0;
      } else {
        intake_mult = -1 ;
      }
    }

    motors::left_drive.move(left_motor_speed);
    motors::right_drive.move(right_motor_speed);

    motors::left_lift.move(config::lift_base_speed * lift_mult);
    motors::right_lift.move(config::lift_base_speed * lift_mult);

    motors::left_intake.move(config::intake_base_speed * intake_mult);
    motors::right_intake.move(config::intake_base_speed * intake_mult);

    iter++;

    if ((iter % config::debug_interval == 0) && config::debug) {
      write_debug_to_screen();
    }
  
    pros::delay(10);

  }
}
