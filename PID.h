#ifndef PID_H
#define PID_H
 
class PID
{
    public:
        PID();
        float control(float target, float nowrpm);
        float PI_lateD(float target, float nowrpm);
        float control_P(float target, float nowrpm, float new_Kp);
        float control_PI(float target, float nowrpm);
        void setParameter(float new_Kp, float new_Ki, float new_Kd);
        void setParameter(float new_Ku, float new_Pu);
        void reset(float target);
 
        float Ku;
        float Pu;
        float Kp;
        float Ti;
        float Td;
        float Ki;
        float Kd;
        
        private:
        float integral;
        float prev_hensa;
        float nowtime;
        float prev_time;
        float lateD;
};
 
#endif
 
