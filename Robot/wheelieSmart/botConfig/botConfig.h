#include "Arduino.h"


// this is a configuration file for the WheelieSmart.ino 
// sketch.
// Fill the variables with the appropriate values for your
// network requirements, robot pin locations, bin schedule
// and server's HTTP request URL

class botConfig {
public: 
    //MOTOR pins: {en1, in1, in2, in3, in4, en2}
    byte motorPins[6] = {1, 2, 3, 4, 5, 6};
    //IR_SENSOR pins: {left, mid, right}
    byte IRPins[3] = {7, 8, 9};
    //US_SENSOR pins: {TRIG, ECHO}
    byte ultraSoundPins[3] = {10, 11, 12};
    //WiFi Details:
    const char* SSID = "exampleWiFiName";
    const char* password = "eX3amplePA55w0rd";
    //Server HTTP request URL:
    const String serverUrl = "www.server.com";
    //Bin time out (HH):
    const int binOutHrs = 06;
    //Bin time out (MM):
    const int binOutMins = 00;
    //Bin time in (HH):
    const int binInHrs = 19;
    //Bin time in (MM):
    const int binInMins = 00;
    //bin id 
    const char* binName = "insert your bin's name from the WheeelieSmart app here";
    //sample JSON string
    char input[200] = "{\"bName\":\"test\",\"bCode\": \"01\",\"day\":\"Tuesday\"}";
};