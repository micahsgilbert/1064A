#include "auton_skills.h"
#include "auton.h"
#include "motors.h"

void auton_skills() {
  motors::left_lift.move(63);
  motors::right_lift.move(63);
  pros::delay(2000);
  motors::left_lift.move(127);
  motors::right_lift.move(127);
  pros::delay(5000);
  motors::left_lift.move(0);
  motors::right_lift.move(0);
  return;
}