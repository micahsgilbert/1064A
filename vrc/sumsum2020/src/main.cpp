/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Azriel                                           */
/*    Created:      Tue Apr 21 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/



#include "vex.h"

using namespace vex;

int main() {

  while(true)
  FLmotor.spin(fwd,(controller1.Axis2.value()),rpm);

  RLmotor.spin(fwd,(controller1.Axis2.value()),rpm);

  FRmotor.spin(fwd,(controller1.Axis2.value()),rpm);

  RRmotor.spin(fwd,(controller1.Axis2.value()),rpm);

  vexcodeInit();
  
}
