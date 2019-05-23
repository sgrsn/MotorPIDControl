#include "MotorControl.h"

MotorControl::MotorControl(int pin1, int pin2, int pin3, int pin4, int pin_pwm)
{
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  _pin_pwm = pin_pwm;
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
}

void MotorControl::control(int8_t value)
{
  prev_state = state;
  if(value > 0)
  {
    state = FORWARD;
    analogWrite(_pin_pwm, value);
  }
  else if(value < 0)
  {
    state = BACK;
    analogWrite(_pin_pwm, abs(value));
  }
  else
  {
    state = STOP;
    analogWrite(_pin_pwm, 255);  // output max power (duty=1)
  }

  if(state != prev_state)
  {
    digitalWrite(_pin1, 0);
    digitalWrite(_pin2, 0);
    digitalWrite(_pin3, 0);
    digitalWrite(_pin4, 0);
    delay(break_time);
  }
  digitalWrite(_pin1,  state     &1);
  digitalWrite(_pin2, (state>>1) &1);
  digitalWrite(_pin3, (state>>2) &1);
  digitalWrite(_pin4, (state>>3) &1);
}

void MotorControl::controlFree()
{
  digitalWrite(_pin1, 0);
  digitalWrite(_pin2, 0);
  digitalWrite(_pin3, 0);
  digitalWrite(_pin4, 0);
}
