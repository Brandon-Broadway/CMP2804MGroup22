#include "Motors.h"
//byte pins[] == {EN_LEFT, IN1, IN2, IN3, IN4, EN_RIGHT}
Motors::Motors(byte pins[]) {
    //store pin locations in byte variables
    EN_LEFT     = pins[0];
    L_MOTOR     = pins[1];
    L_MOTOR_REV = pins[2];
    R_MOTOR     = pins[3];
    R_MOTOR_REV = pins[4];
    EN_RIGHT    = pins[5];
}     

void Motors::begin() {
    //write to serial confirming begin function is called
    Serial.println("MOTORS:\t6 pin 2X DCmotor constructed");
    //set pins to OUTPUT mode
    // pinMode(EN_LEFT, OUTPUT);
    pinMode(L_MOTOR, OUTPUT);
    pinMode(L_MOTOR_REV, OUTPUT);
    pinMode(R_MOTOR, OUTPUT);
    pinMode(R_MOTOR_REV, OUTPUT);
    // pinMode(EN_RIGHT, OUTPUT);
}

void Motors::beginPwm() {
    //write to serial confirming PWM setup
    Serial.println("MOTORS:\tsetting up pwm lines for EN1 & EN2");
    //setup and attach pwm settings using default values from Motors.h
    ledcSetup(pwmChannelL, freq, resolution);
    ledcSetup(pwmChannelR, freq, resolution);
    ledcAttachPin(EN_LEFT, pwmChannelL);
    ledcAttachPin(EN_RIGHT, pwmChannelR);
}

void Motors::forward() {
    //turn both motors forwards
    digitalWrite(L_MOTOR, HIGH);
    digitalWrite(L_MOTOR_REV, LOW);
    digitalWrite(R_MOTOR, HIGH);
    digitalWrite(R_MOTOR_REV, LOW);
    Serial.println("MOTORS:\tfwd");     
}

void Motors::left() {   
    //turn lef motor forwards
    digitalWrite(L_MOTOR, HIGH);
    digitalWrite(L_MOTOR_REV, LOW);
    //turn right motor backwards
    digitalWrite(R_MOTOR, LOW);
    digitalWrite(R_MOTOR_REV, HIGH);
    Serial.println("MOTORS:\tleft");
}

void Motors::right() {
    //turn left motor backwards
    digitalWrite(L_MOTOR, LOW);
    digitalWrite(L_MOTOR_REV, HIGH);
    //turn right motor forwards
    digitalWrite(R_MOTOR, HIGH);
    digitalWrite(R_MOTOR_REV, LOW);
    Serial.println("MOTORS:\tright");
}

void Motors::reverse() {
    //turn both motors backwards
    digitalWrite(L_MOTOR, LOW);
    digitalWrite(L_MOTOR_REV, HIGH);
    digitalWrite(R_MOTOR, LOW);
    digitalWrite(R_MOTOR_REV, HIGH);
    Serial.println("MOTORS:\trev");
}

void Motors::stopBot() {
    //stop both motors
    digitalWrite(L_MOTOR, LOW);
    digitalWrite(L_MOTOR_REV, LOW);
    digitalWrite(R_MOTOR, LOW);
    digitalWrite(R_MOTOR_REV, LOW);
}

void Motors::setSpeed(int left, int right) {
    //write the duty cycle values passed as variables...
    //to both pwmChannels
    ledcWrite(pwmChannelL, left);
    ledcWrite(pwmChannelR, right);
}

void Motors::setSpeedAdv(int left, int right, int freqIn, int resIn) {
    //set passed values for frequency and resolution to vars in Motors.h
    freq = freqIn;
    resolution = resIn;
    //print new values to serial
    Serial.print("freq: ");
    Serial.print(freq);
    Serial.print(",\t||\tRes");
    Serial.println(resolution);
    //apply new frequency and resolution with beginPwm function
    beginPwm();
    //apply new duty cycle values with setSpeed function
    setSpeed(left, right);
}



