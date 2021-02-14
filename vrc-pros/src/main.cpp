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

void on_left_button() {
  auton_config::side = 1 - auton_config::side;
}

void on_center_button() {
  auton_config::center = !auton_config::center;
}

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
  pros::lcd::register_btn0_cb(on_left_button);
  pros::lcd::register_btn1_cb(on_center_button);
}

void autonomous() {
  auton(auton_config::side, auton_config::center);
}

void opcontrol() {

  //auton(1, true);
  //auton_skills()

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
      int direction = controller.get_analog(ANALOG_LEFT_X);
      left_motor_speed = (controller.get_analog(ANALOG_LEFT_Y) + direction) / 1.5;
      right_motor_speed = (controller.get_analog(ANALOG_LEFT_Y) - direction) / 1.5;
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

    if (controller.get_digital(DIGITAL_L2)) {
      intake_mult = 1;
    }

    else if (controller.get_digital(DIGITAL_L1)) {
      intake_mult = -1;
    }

    else {
      intake_mult = 0;
    }

    motors::left_drive.move(left_motor_speed);
    motors::right_drive.move(right_motor_speed);

    motors::left_lift.move(config::lift_base_speed * lift_mult);
    motors::right_lift.move(config::lift_base_speed * lift_mult);

    motors::left_intake.move(config::intake_base_speed * intake_mult);
    motors::right_intake.move(config::intake_base_speed * intake_mult);

    iter++;

    pros::lcd::print(7, "[SIDE]      [CENTER]");
    
    if (auton_config::side == 0) {
      pros::lcd::print(0, "LEFT AUTON");
    } else {
      pros::lcd::print(0, "RIGHT AUTON");
    }

    if (auton_config::center) {
      pros::lcd::print(1, "RUN CENTER");
    } else {
      pros::lcd::print(1, "DO NOT RUN CENTER");
    }
    
  
    pros::delay(10);

  }
}
