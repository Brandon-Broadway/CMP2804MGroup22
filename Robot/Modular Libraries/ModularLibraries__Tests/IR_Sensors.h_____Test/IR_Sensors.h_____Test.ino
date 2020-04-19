//this is a testing sketch to make sure the IR_Sensors.h library is functioning correctly.
//Make sure the IR_Sensors.h librarie is saved in your PC's ..../Arduino/libraries directory.

//Change the "#define"-ed pin locations to those which are connected to your the respective
//IR Sensors on you build.

//To make sure this is working correctly, place each sensor over something black, then something not black
//when the sensor is over something black, the name of that sensor will be printed to the Serial Monitor (at 115200 baud)

#include <Arduino.h>
#include <IR_Sensors.h>

//change these to the appropriate IR pin locations for your build
#define IR_LEFT 32
#define IR_MID 35
#define IR_RIGHT 34

byte IRpins[] = {IR_LEFT, IR_MID, IR_RIGHT};

IR_Sensors IR = IR_Sensors(IRpins);

void setup() {
  

    //start serial comms on 115200 baud
    Serial.begin(115200);

}
char prevSense;


void loop() {
    
    byte leftSense, midSense, rightSense;

    IR.ReturnIR(leftSense, midSense, rightSense);

    
    short totalSense = (midSense + leftSense + rightSense);

    if (totalSense == 1) {
        if (leftSense == 1 && prevSense != 'l') {
            prevSense = 'l';
            Serial.println(prevSense);
        } else if(midSense == 1 && prevSense != 'm'){
            prevSense = 'm';
            Serial.println(prevSense);
        } else if (rightSense == 1 && prevSense != 'r') {
            prevSense = 'r';
            Serial.println(prevSense);
        }
    } if (totalSense == 3 && prevSense != 'a' ) {
      prevSense  = 'a';
      Serial.println(prevSense);
      
    }
}
