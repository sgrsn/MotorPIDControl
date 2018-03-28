#include "PID.h"
#include <Arduino.h>
 
PID::PID()
{
    integral    = 0;
    prev_hensa  = 0;
    nowtime     = 0;
    prev_time   = 0;
    lateD      = 0;
}
float PID::control(float target, float nowrpm)
{
    nowtime = micros();
    float hensa = target - nowrpm;
    float dt = 1000000 / (nowtime - prev_time);
    integral += (hensa + prev_hensa) / 2 * dt;
    float differential = (hensa - prev_hensa) / dt;
    float sousaryou = Kp*hensa + Ki*integral + Kd*differential;
    prev_hensa = hensa;
    prev_time = micros();
    return sousaryou;
}
float PID::PI_lateD(float target, float nowrpm)
{
    nowtime = micros();
    float hensa = target - nowrpm;
    float dt = nowtime - prev_time;
    integral += (hensa + prev_hensa) / 2 * dt;
    float sousaryou = Kp*hensa + Ki*integral + Kd*lateD;
    prev_hensa = hensa;
    prev_time = micros();
    lateD = (hensa - prev_hensa) / dt;
    return sousaryou;
}
float PID::control_P(float target, float nowrpm, float new_Kp)
{
    float hensa = target - nowrpm;
    float sousaryou = new_Kp*hensa;
    return sousaryou;
}
float PID::control_PI(float target, float nowrpm)
{
    Kp = 0.45 * Ku;
    Ti = 0.83 * Pu;
    Ki = (1 / Ti) * Kp;
    nowtime = micros();
    float hensa = target - nowrpm;
    float dt = nowtime - prev_time;
    integral += (hensa + prev_hensa) / 2 * dt;
    float sousaryou = Kp*hensa + Ki*integral;
    prev_hensa = hensa;
    prev_time = micros();
    return sousaryou;
}
void PID::setParameter(float new_Kp, float new_Ki, float new_Kd)
{  
  Kp = new_Kp;
  Ki = new_Ki;
  Kd = new_Kd;
}
void PID::setParameter(float new_Ku, float new_Pu)
{  
    Ku = new_Ku;
    Pu = new_Pu;
    
    Kp = 0.60 * Ku;
    Ti = 0.50 * Pu;
    Td = 0.125 * Pu;
    Ki = (1 / Ti) * Kp;
    Kd = Td * Kp;
}
void PID::reset(float target)
{
    integral    = 0;
    prev_hensa  = target;
    prev_time = micros();
}
