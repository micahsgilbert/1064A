#include "config.h"

/*
DRIVE MODES
0: tank: left stick controls left drive, right stick controls right drive,
1: arcade: left stick controls all drive
2: custom: left stick controls l/r, right stick controls f/b
*/

/*
CONFIGURATION
lift_base_speed and intake_base_speed are the base speeds for the lift and intake, which are multiplied by -1,-,0,1 or 2 as defined by lift_mult and intake_mult.
debug is debug
*/

/*
DEBUG
currently just writes motor speeds to the screen
interval is each iteration, about 10ms
*/

namespace config {
  int drive_mode = 0;
  int lift_base_speed = 63;
  int intake_base_speed = 127;
  bool debug = true;
  int debug_interval = 50;
}