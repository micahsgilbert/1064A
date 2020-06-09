#include "vex.h"
using namespace vex;

brain Brain;

  controller controller1 = primary; 
    //drive things
  motor FLmotor = motor (PORT1,ratio6_1, true);

  motor FRmotor = motor (PORT2,ratio6_1, false);

  motor RLmotor = motor (PORT3,ratio6_1, true);

  motor RRmotor = motor (PORT4, ratio6_1,false); 



void vexcodeInit(void) {
}