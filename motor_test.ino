#include "RotaryEncoder.h"
#include "MotorControl.h"
#include "PID.h"

void tickPath();
RotaryEncoder encoder = RotaryEncoder(2, 3, &tickPath);
MotorControl motor(12, 13, 4, 5, 6);
PID pid;

void tickPath()
{
  encoder.tick();
}
void setup()
{
  Serial.begin(57600);
  pid.setParameter(0.000006, 0.151515);
}
float angle = 0;
float prev_angle = 0;
int nowtime = 0;
int prev_time = 0;
float omega_sumpling[] = {0,0,0,0,0,0,0,0,0,0};
float m_omega = 0;
float omega = 0;
float prev_omega = 0;
bool controlFlag = false;

float target_omega = 2000;

int sumpling_length = sizeof(omega_sumpling) / sizeof(float);

void loop()
{
  prev_angle = angle;
  angle = encoder.getAngle();
  nowtime = micros();
  omega = (angle - prev_angle) * 1000000 / (nowtime - prev_time);
  prev_time = micros();
  if(omega != 0)
  {
    Serial.print(micros());
    Serial.print(", ");
    Serial.println(omega);
  }
  delay(15);

  if(controlFlag)
  {
    float e = pid.control(target_omega, omega);
    motor.control(e);
  }
  else
  {
    motor.control(0);
  }
}

void serialEvent()
{
  if(Serial.available() > 0)
  {
    pid.reset(target_omega);
    controlFlag = !controlFlag;
  }
}

