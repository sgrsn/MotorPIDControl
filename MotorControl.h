#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <lbed.h>

#define break_time 1  //[ms]

#define FORWARD 5
#define BACK 10
#define STOP 3

class MotorControl : public BusOut, PwmOut
{
  public:
  MotorControl(int pin1, int pin2, int pin3, int pin4, int pin_pwm);
  void control(float value);
  void controlFree();

  private:
  int state = STOP;
  int prev_state = STOP;
};

#endif
