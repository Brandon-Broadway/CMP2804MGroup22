//this is a testing sketch to make sure that the UltraSound.h library is functioning correctly.
//Make sure the UltraSound.h librarie is saved in your PC's ..../Arduino/libraries directory.

//Change the "#define"-ed pin locations to those which are connected to your the respective
//US sensor pins on your build.

//to make sure the US sensor is working place something in front of it, the Serial monitor should 
//print the distance in centimeters between the thing and the US sensor.

//if you place something closer than the variable "distance" cm which is at default 5cm
//the onboard led of your board will double flash until the obstruction is no longer too close


#include "UltraSound.h"

//change these to the appropirate ultrasound pins for your build
int TRIG_PIN = 22;
int ECHO_PIN = 23;
//ESP32 has no LED_BUILTIN, if using arduino board, comment the below variable declaration
int LED_BUILTIN = 2;
//construct object of class
UltraSound US = UltraSound(TRIG_PIN, ECHO_PIN);

//testing distance in cm
int distance = 5;

void setup() {
   
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

}

void loop() {
    //print current distance from US to serial
    int d = US.CheckDistance();    
    Serial.print("distance: ");
    Serial.println(d);

    if (US.CloserThan(distance)) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
}
