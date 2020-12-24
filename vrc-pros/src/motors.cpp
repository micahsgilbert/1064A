#include "motors.h"
#include "main.h"

namespace motors {
  pros::Motor left_drive(1);
  pros::Motor right_drive(2, true);

  pros::Motor left_lift(3, true);
  pros::Motor right_lift(4);

  pros::Motor left_intake(5);
  pros::Motor right_intake(6, true);
}