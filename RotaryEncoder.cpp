#include "Arduino.h"
#include "RotaryEncoder.h"

const int8_t TABLE[] = {0, -1,  1,  0, 1,  0,  0, -1, -1,  0,  0,  1, 0,  1, -1,  0  };

RotaryEncoder::RotaryEncoder(int pin1, int pin2, void (*fptr)() )
{
  _pin1 = pin1;
  _pin2 = pin2;
  pinMode(_pin1, INPUT);
  pinMode(_pin2, INPUT);
  digitalWrite(_pin1, INPUT_PULLUP);
  digitalWrite(_pin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_pin1), fptr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(_pin2), fptr, CHANGE);

  _oldState = 3;
  _position = 0;
}

long  RotaryEncoder::getPosition() {
  return _position;
}

float  RotaryEncoder::getAngle() {
  return (float)_position * 360/200;
}

void RotaryEncoder::tick(void)
{
  int sig1 = digitalRead(_pin1);
  int sig2 = digitalRead(_pin2);
  int8_t thisState = sig1 | (sig2 << 1);

  if (_oldState != thisState) {
    _position += TABLE[thisState | (_oldState<<2)];
    _oldState = thisState;
  }
}
