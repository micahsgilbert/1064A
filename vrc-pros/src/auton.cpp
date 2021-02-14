#include "auton.h"
#include "motors.h"
#include "inertial.h"

using namespace inertial_ns;
namespace auton_config {
  int side = 0;
  bool center = true;
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

void driveUnits(int left, int right) {
  motors::left_drive.move_relative(left, 110);
  motors::right_drive.move_relative(right, 110);
  pros::delay((int)(max(abs(left), abs(right)) * 0.8));
}

void rotate(int degrees) {
  int target = inertial.get_rotation() + degrees;
  if (inertial.get_rotation() < target) {
    motors::left_drive.move(90);
    motors::right_drive.move(-90);
    while(inertial.get_rotation() < target - 5) {
      pros::delay(10);
    }
  } else {
    motors::left_drive.move(-90);
    motors::right_drive.move(90);
    while(inertial.get_rotation() > target + 5) {
      pros::delay(10);
    }
  }
  
  motors::left_drive.move(0);
  motors::right_drive.move(0);
}

void auton(int side, bool center) {
  inertial.reset();
  /*
  SIDE
  0: left
  1: right

  CENTER:
  true: score center
  false: do not
  */

  // deploy top lift

  motors::left_lift.move(-63);
  motors::right_lift.move(-63);
  pros::delay(500);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  motors::left_lift.move(63);
  motors::right_lift.move(63);
  pros::delay(600);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  // give the sensor time to calibrate
  //pros::delay(500);

  motors::left_intake.move(-127);
  motors::right_intake.move(-127);


  if (side == 0) {
    driveUnits(2200,2200);
    rotate(-60);
  } else {
    driveUnits(2000,2000);
    rotate(70);
  }

  driveUnits(1500,1500);
  
  // deploy preload and take in tower ball

  motors::left_lift.move(127);
  motors::right_lift.move(127);
  pros::delay(1700);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  motors::left_intake.move(127);
  motors::right_intake.move(127);

  pros::delay(200);

  //move back
  if (side == 0) {
    driveUnits(-1900,-1900);
  } else {
    driveUnits(-2300,-2300);
  }


  motors::left_intake.move(0);
  motors::right_intake.move(0);

  if (!center) {
    return;
  }

  if (side == 0) {
    rotate(-135);
    driveUnits(1650,1650);
  } else {
    rotate(-210);
    driveUnits(1750,1750);
  }


  if (side == 0) {
    rotate(90);
  } else {
    rotate(-80);
  }

  driveUnits(1290, 1290); // slams into tower to correct itself for inaccuracies, so back it off a bit before putting ball in

  //driveUnits(-200,-200);
  pros::delay(100);

  motors::left_lift.move(127);
  motors::right_lift.move(127);
  pros::delay(2500);
  motors::left_lift.move(0);
  motors::right_lift.move(0);
  

  //motors::left_intake.move(127);
  //motors::right_intake.move(127);
  driveUnits(-1000,-1000);
  //motors::left_intake.move(127);
  //motors::right_intake.move(127);
}