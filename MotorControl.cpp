#include "MotorControl.h"

MotorControl::MotorControl(int pin1, int pin2, int pin3, int pin4, int pin_pwm) : BusOut(pin1, pin2, pin3, pin4), PwmOut(pin_pwm)
{
}

void MotorControl::control(float value)
{
  prev_state = state;
  if(value > 0)
  {
    state = FORWARD;
    PwmOut::write(value);
  }
  else if(value < 0)
  {
    state = BACK;
    PwmOut::write(-value);
  }
  else
  {
    state = STOP;
    PwmOut::write(1);
  }

  if(state != prev_state)
  {
    BusOut::write(0);
    delay(break_time);
  }
  BusOut::write(state);
}

void MotorControl::controlFree()
{
  BusOut::write(0);
}



