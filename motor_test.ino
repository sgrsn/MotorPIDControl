#include "RotaryEncoder.h"
#include "MotorControl.h"
#include "PID.h"

void tickPath();
RotaryEncoder encoder = RotaryEncoder(2, 3, &tickPath);
MotorControl motor(12, 13, 4, 5, 6);
PID pid;
int32_t Registar[0x80] = {};

void tickPath()
{
  encoder.tick();
}
void setup()
{
  Serial.begin(115200);
  //pid.setParameter(0.00080, 0, 0);
  pid.setParameter(0.00080, 0.123077);
}
float angle = 0;
float prev_angle = 0;
int nowtime = 0;
int prev_time = 0;
float omega = 0;
int controlFlag = 0;

float target_omega = 2500;

void loop()
{
  pidSeq();
}

void pidSeq()
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

  if(controlFlag==1)
  {
    float e = pid.control(target_omega, omega);
    motor.control(e);
    Serial.print(e);
    Serial.print(", ");
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
    Serial.read();
    pid.reset(target_omega);
    controlFlag = !(controlFlag);
  }
}

void test()
{
  motor.control(1);
  delay(3000);
  motor.control(0);
  delay(3000);
  motor.control(-1);
  delay(3000);
  motor.control(0);
  delay(3000);
}
