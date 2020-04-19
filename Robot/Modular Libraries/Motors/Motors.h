#include <Arduino.h>

class Motors
{
public:
    Motors(byte pins[]);
    void begin();
    void beginPwm();
    void forward();
    void left();
    void right();
    void reverse();
    void stopBot();
    
    void setSpeed(int left, int right);
    void setSpeedAdv(int left, int right, int freqIn, int resIn);
    //direction char =  f, r, b, l ==> forward, right, back, left 
    char direction;
    byte L_MOTOR;
    byte L_MOTOR_REV;
    byte R_MOTOR;
    byte R_MOTOR_REV;
    byte EN_LEFT;
    byte EN_RIGHT;
    bool ENABLE_ON;
    int freq = 1000; 
    const int pwmChannelL = 0; 
    const int pwmChannelR = 1;
    int resolution = 8;
};




