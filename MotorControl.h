#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

#define break_time 1  //[ms]

#define FORWARD 5         // 0101
#define BACK 10           // 1010
#define STOP 3  //(BREAK) // 0011

class MotorControl
{
  public:
  MotorControl(int pin1, int pin2, int pin3, int pin4, int pin_pwm);
  void control(int8_t value);
  void controlFree();   // set motor Coast

  private:
  int state = STOP;
  int prev_state = STOP;
  int _pin1, _pin2, _pin3, _pin4, _pin_pwm;
};

#endif
