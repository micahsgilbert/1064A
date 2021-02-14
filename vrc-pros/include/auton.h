#ifndef AUTON_H
#define AUTOH_H

int max(int a, int b);
void driveUnits(int left, int right);
void rotate(int degrees);
void auton(int side, bool center);
namespace auton_config{
  extern int side;
  extern bool center;
}

#endif