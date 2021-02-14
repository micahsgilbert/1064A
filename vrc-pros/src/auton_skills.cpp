#include "auton_skills.h"
#include "auton.h"
#include "motors.h"
#include "inertial.h"

using namespace inertial_ns;

void auton_skills() {
  inertial.reset();
  //pros::delay(3000);

  // deploy intake
  motors::left_lift.move(-100);
  motors::right_lift.move(-100);

  pros::delay(500);  

  motors::left_lift.move(0);
  motors::right_lift.move(0);

  pros::delay(200);

  motors::left_lift.move(63);
  motors::right_lift.move(63);
  pros::delay(200);
  motors::left_lift.move(127);
  motors::right_lift.move(127);
  pros::delay(2400);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  pros::delay(200);

  // pull away from corner goal
  driveUnits(-1400,-1400);

  pros::delay(250);

  // rotate to face out
  rotate(115);

  // have lift moving up and intake taking in, in order to get the ball outside of the side goal

  motors::left_intake.move(-127);
  motors::right_intake.move(-127);
  motors::left_lift.move(100);
  motors::right_lift.move(100);

  // drive towards the center goal

  driveUnits(2900,2900);

  // stop lift and intake, but wait a bit so we're sure the ball makes it in
  pros::delay(1000);
  motors::left_intake.move(0);
  motors::right_intake.move(0);
  motors::left_lift.move(0);
  motors::right_lift.move(0);

  // rotate to face the goal

  rotate(-45);
  driveUnits(-60,-60);
  rotate(-45);

  // drive to the goal

  driveUnits(500,500);

  // launch the ball in, and start intakes to descore the blue ball

  motors::right_lift.move(127);
  motors::left_lift.move(127);
  pros::delay(3000);
  motors::right_lift.move(0);
  motors::left_lift.move(0);

  //pull out

  driveUnits(-1000,-1000);
  rotate(-165);

  // approach center tower
  driveUnits(1500,1500);
  pros::delay(200);

  //descore the center (currently just rams it, should be improved)
  driveUnits(-500,-500);
  rotate(-5);
  pros::delay(200);
  driveUnits(600,600);
  pros::delay(200);
  driveUnits(-500,-500);
  pros::delay(200);
  driveUnits(600,600);
  pros::delay(200);
  driveUnits(-500,-500);
  pros::delay(200);
  driveUnits(600,600);
  pros::delay(200);
  driveUnits(-500,-500);
  pros::delay(200);
  driveUnits(600,600);
  pros::delay(200);
  driveUnits(-500,-500);

}