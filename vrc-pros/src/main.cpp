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
}

void driveFor(int left, int right, int time) {
  left_drive.move(left);
  right_drive.move(right);
  pros::delay(time);
  left_drive.move(0);
  right_drive.move(0);
}

void auton() {

  left_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
  right_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);

  // move forward a bit
  driveFor(100,100,250);

  // deploy top lift

  left_lift.move(63);
  right_lift.move(63);
  pros::delay(250);
  left_lift.move(127);
  right_lift.move(127);

  // wait for preload to move to top
  pros::delay(1000);

  // stop lift, move to corner
  left_lift.move(0);
  right_lift.move(0);

  // move back

  driveFor(-100,-100,250);

  // rotate left

  driveFor(100,-100,200);

  // move back

  driveFor(-100,-100,500);

  // rotate right
  
  driveFor(-100,100,160);

  // move forward

  driveFor(100,100,600);

  

  // rotate left

  // move forward


  right_drive.move(0);
  left_drive.move(0);

  left_drive.set_brake_mode(MOTOR_BRAKE_COAST);
  right_drive.set_brake_mode(MOTOR_BRAKE_COAST);


}

void autonomous() {
  auton();
  
}

void write_debug_to_screen() {
  int left_lift_vel = (int)left_lift.get_actual_velocity();
  int right_lift_vel = (int)right_lift.get_actual_velocity();

  pros::lcd::print(0,"Lift Velocities:  L: %i R: %i",(int)left_lift.get_actual_velocity(),(int)right_lift.get_actual_velocity());
}

void opcontrol() {

  auton();

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
