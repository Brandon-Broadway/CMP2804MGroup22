//this is a testing sketch to make sure the Mtorss.h library is functioning correctly.
//Make sure the Motors.h library is saved in your PC's ..../Arduino/libraries directory.

//Change the "#define"-ed pin locations to those which are connected to your the respective
//l298n pins on your build.

//To make sure this is working correctly, load the sketch onto your artefact, and clear a moderately large space on the floor
//place the artefact on the floor with the power on and this sketch uploaded.
//You should see the bot do loops of a moving forwards, moving backwards, turning right & turning left at increaing speeds

#include <Arduino.h>
#include <Motors.h>

byte pins[] = {26, 27, 14, 5, 18, 19};



Motors frontWheels(pins);

void setup() {
  //setup serial on 115200 baud
  Serial.begin(115200);
  //complete setting up Motors obj
  frontWheels.begin();
  frontWheels.beginPwm();
  frontWheels.setSpeedAdv(100, 100, 500, 8);

}

//do loops of a moving forwards, moving backwards, turning right & turning left at increaing speeds
void loop() {
  //set initial frequency and duty cycle
  int freq = 500;
  int i = 120;
  //loop through pwm duty cycles from 120 -> 250
  while (i < 250) {
      //conditional statements to control pwm frequency balance against changing duty cycle
      if (i > 160 && i < 200) 
      {
        freq = 5000;
      } 
      else if (i >= 200){
        freq = 20000;
      } else {
        freq = 500;
      }
      //set sduty cycle and frequency to values chosen above
      frontWheels.setSpeedAdv(i, i, freq, 8);
      delay(300);
      //forward for 400ms
      frontWheels.forward();
      delay(400);
      //reverse for 400ms
      frontWheels.reverse();
      delay(400);
      //forward for 400ms
      frontWheels.right();
      delay(400);
      //forward for 400ms
      frontWheels.left();
      delay(400);
      i += 10;
  }
}
