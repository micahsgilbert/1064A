#include "auton.h"
#include "motors.h"

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

void driveUnits(int left, int right) {
  motors::left_drive.move_relative(left, 127);
  motors::right_drive.move_relative(right, 127);
  pros::delay((int)(max(abs(left), abs(right)) * 0.8));
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

  motors::left_lift.move(63);
  motors::right_lift.move(63);
  pros::delay(500);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  // move forward

  driveUnits(2000,2000);

  // rotate

  pros::delay(100);

  if (side == 0) {
    rotate(-150);
  } else {
    rotate(152);
  }

  // move forward up to corner tower

  driveUnits(1690,1690);
  driveUnits(-50,-50);
  pros::delay(100);

  // deploy preload and take in tower ball

  motors::left_lift.move(127);
  motors::right_lift.move(127);
  pros::delay(1300);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  pros::delay(200);

  driveUnits(-2000,-2000);

  if (side == 0) {
    rotate(-130);
  } else {
    rotate(135);
  }


  driveUnits(2200,2200);

  pros::delay(200);

  if (side == 0) {
    rotate(130);
  } else {
    rotate(-90);
  }

  driveUnits(1290, 1290); // slams into tower to correct itself for inaccuracies, so back it off a bit before putting ball in

  driveUnits(-200,-200);
  pros::delay(100);

  motors::left_lift.move(127);
  motors::right_lift.move(127);
  pros::delay(1200);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  motors::left_drive.move(0);
  motors::right_drive.move(0);
}