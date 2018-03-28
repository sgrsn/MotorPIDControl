#ifndef RotaryEncoder_h
#define RotaryEncoder_h
#include "Arduino.h"

class RotaryEncoder
{
public:
  RotaryEncoder(int pin1, int pin2, void (*fptr)() );
  long  getPosition();
  float  getAngle();
  void setPosition(long newPosition);
  void tick(void);
private:
  int _pin1, _pin2;
  int8_t _oldState;
  long _position;
};

#endif
