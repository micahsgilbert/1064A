#include "main.h"

/*
CONTROLS
left & right sticks control drive as configured
up/down buttons control lift. each button toggles between its direction and off
x/b buttons control intake, same way as lift
*/

/*
DRIVE MODES
0: tank: left stick controls left drive, right stick controls right drive,
1: arcade: left stick controls all drive
2: custom: left stick controls l/r, right stick controls f/b
*/

const int drive_mode = 0;

/*
CONFIGURATION
lift_speed and intake_speed are the base speeds for the lift and intake, which are multiplied by -1,-,0,1 or 2 as defined by lift_mult and intake_mult.
debug is debug
*/

const int lift_speed = 63;
const int intake_speed = 63;

/*
DEBUG
currently just writes motor speeds to the screen
interval is each iteration, about 10ms
*/

const bool debug = true;
const int debug_interval = 50;

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Motor left_drive(1);
pros::Motor right_drive(2, true);

pros::Motor left_lift(3, true);
pros::Motor right_lift(4);

pros::Motor left_intake(5);
pros::Motor right_intake(6, true);

void disabled() {}

void competition_initialize() {}

void initialize() {
  pros::lcd::initialize();
  left_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  right_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

void driveUnits(int left, int right) {
  left_drive.move_relative(left, 105);
  right_drive.move_relative(right, 105);
  pros::delay(max(left, right) * 1.5);
}

void rotate(int degrees) {
  driveUnits(degrees * 10, degrees * -10);
}

void auton(int side) {
  /*
  SIDE
  0: left
  1: right
  */

  // deploy top lift

  left_lift.move(63);
  right_lift.move(63);
  pros::delay(500);
  left_lift.move(0);
  right_lift.move(0);

  // move forward

  driveUnits(2100,2100);

  // rotate

  if (side == 0) {
    rotate(-135);
  } else {
    rotate(135);
  }

  // move forward up to corner tower

  driveUnits(1600,1600);

  // deploy preload and take in tower ball

  left_lift.move(127);
  right_lift.move(127);
  pros::delay(1300);
  left_lift.move(0);
  right_lift.move(0);

  right_drive.move(0);
  left_drive.move(0);

  pros::delay(4000);

}

void autonomous() {
  auton(0);
}

void write_debug_to_screen() {
  int left_lift_vel = (int)left_lift.get_actual_velocity();
  int right_lift_vel = (int)right_lift.get_actual_velocity();

  pros::lcd::print(0,"Lift Velocities:  L: %i R: %i",(int)left_lift.get_actual_velocity(),(int)right_lift.get_actual_velocity());
}

void opcontrol() {

  int left_motor_speed = 0;
  int right_motor_speed = 0;

  int lift_mult = 0;
  int intake_mult = 0;

  uint32_t iter = 0;

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

    if (controller.get_digital_new_press(DIGITAL_X)) {
      if (intake_mult == 1) {
        intake_mult = 0;
      } else {
        intake_mult = 1;
      }
    }

    if (controller.get_digital_new_press(DIGITAL_B)) {
      if (intake_mult == -1) {
        intake_mult = 0;
      } else {
        intake_mult = -1 ;
      }
    }

    left_drive.move(left_motor_speed);
    right_drive.move(right_motor_speed);

    left_lift.move(lift_speed * lift_mult);
    right_lift.move(lift_speed * lift_mult);

    left_intake.move(intake_speed * intake_mult);
    right_intake.move(intake_speed * intake_mult);

    iter++;

    if ((iter % 20 == 0) && debug) {
      write_debug_to_screen();
    }
  
    pros::delay(10);

  }
}
