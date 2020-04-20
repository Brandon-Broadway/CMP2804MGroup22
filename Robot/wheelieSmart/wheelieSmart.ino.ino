#include <WiFi.h>
#include <botConfig.h>
#include <HTTPClient.h>
#include <time.h>
#include <ArduinoJson.h>
#include <Motors.h>
#include <UltraSound.h>
#include <IR_Sensors.h>

//botConfig object for values from config file
botConfig bot;

//byte vars for IR sensor results
byte leftSense, midSense, rightSense;
//char var for storing previous IR signal
char prevSense;
//int var to store length of turn-in to straighten up for the same time Using millis()
int prevTurn;

//construct motor pair object
Motors frontWheels(bot.motorPins);
//construct UltraSound object
UltraSound uS(bot.ultraSoundPins[0], bot.ultraSoundPins[1]);
//construct IR triplets object
IR_Sensors IRs(bot.IRPins);

//ntp server deets
const char* ntpServer = "pool.ntp.org";
//time-zone offset
const long  gmtOffset_sec = 3600;
//daylight savings offset
const int   daylightOffset_sec = 00;
//timeinfo obj to store ntp time globally
struct tm timeinfo;

//time out 
const int timeOutHrs = bot.binOutHrs;
const int timeOutMins = bot.binOutMins;
//time in
const int timeInHrs = bot.binInHrs;
const int timeInMins = bot.binInMins;

#define uS_TO_S_FACTOR 1000000  //conversion from microseconds (uS) to seconds (S)
#define uS_TO_Min_FACTOR 60000000  //conversion from microseconds (uS) to minutes (mins)
#define uS_TO_Hr_FACTOR 3600000000 // conversion from microseconds (uS) to hours (Hr)
#define mS_TO_Min_FACTOR 60000     //conversion from milliSeconds to minutes



//bot position = 'i' for in || 'o' for out
RTC_DATA_ATTR char botPos = 'i'; //RTC mem means it will stay the same over reboots/powerloss/deepsleep


//variables to store deserialised json attributes from azure server
const char* bName;
int id;
const char* goingOut;



void printLocalTime()
{    
    while(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        delay(1000);
    }
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
    //begin serial Monitor on 115200 baud
    Serial.begin(115200);
    //delay 
    delay(1000);
    frontWheels.begin();
    delay(500);
    frontWheels.beginPwm();
    delay(500);
    //set 
    frontWheels.setSpeedAdv(200, 200, 40000, 8);
    delay(1000);
    //initialise WiFi obj
    WiFi.begin(bot.SSID, bot.password);
    //wait for Wifi to connect
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    //WiFi Connected
    Serial.println("Connected to the WiFi network");
    Serial.println("botPos: " + botPos);
    //init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(1000);
    printLocalTime();
    //TESTTING JSON STRING FROM server
    //receive JSON payload from http request
    String payload = getPayload();
    //convert String type payload to char[]
    char c_payload[payload.length() + 1];
    strcpy(c_payload, payload.c_str()); 
    //deserialize the JSON payload
    DeserializeJSONString(c_payload);

    //
    //Decomment the 3 lines below to test using test JSON string in botConfig.h
        //Deserialising JSON payload and storing attributes
        //example string
        //DeserializeJSONString(bot.input);
      
    //testing the WhatDay function correctly converts the day code from ntp server to string of name of the day 
    char* day = WhatDay(timeinfo.tm_wday);
    Serial.println("====================\nDay from NTP Server:\t" + String(day));

    //check if bin should go out
    if (RightDay() == true) {
      Serial.println("right day!");
      RightTime();
    } else Serial.println("not right day");
}

void loop() {
    
}

//function to convert day code from NTP server to String "day"
char* WhatDay(int fromSunday) {
  char* day;
  switch (fromSunday){
    case 0: 
      day = "Sunday";
      break;
    case 1:
      day = "Monday";
      break;
    case 2:
      day = "Tuesday";
      break;
    case 3:
      day = "Wednesday";
      break;
    case 4:
      day = "Thursday";
      break;
    case 5:
      day = "Friday";
      break;
    case 6:
      day = "Saturday";
      break;
  }
  return day;
}

bool RightDay() {
    char* NTPday = WhatDay(timeinfo.tm_wday);
    //Serial printing values to find potential errors
//    Serial.print("from NTP: \t");
//    Serial.println(NTPday);
//    Serial.print("from JSON:\t");
//    Serial.println(goingOut);
      
    int comp = strcmp(NTPday, goingOut);
    if (comp == 0) return true;
    else return false;
}

  void RightTime() {
//    Serial.println("botPos: " + String(botPos));
//    Serial.println("NTPtime: " + String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min));
    if (botPos == 'i') { //if bot is in
        if (timeOutHrs == timeinfo.tm_hour) { //if it's the right hour
            if (timeOutMins <= timeinfo.tm_min) { //if it's past the set minute on the hour
//                Serial.println("bring bot out"); //send bot out
                followLine();
                botPos = 'o';
                esp_sleep_enable_timer_wakeup(1 * uS_TO_Hr_FACTOR); //sleep for how many mins there are until NEXT HOUR
//                Serial.println("Sleeping for: " + String(1) + "Hrs"); //report sleep time
                esp_deep_sleep_start();
            } else { //IF RIGHT DAY && right Hour BUT NOT RIGHT Minutes
//                Serial.println("<= 1hr before bins out");
//                Serial.println("timeOutMins: " + String(timeOutMins));
//                Serial.println("timeinfo.tm_min: " + String(timeinfo.tm_min));
                int timeToSleep = (timeOutMins - timeinfo.tm_min) ; //hours mins are left till scheduled out time
                esp_sleep_enable_timer_wakeup(timeToSleep * uS_TO_Min_FACTOR); //sleep for how many mins there are until 
//                Serial.println("Sleeping for: " + String(timeToSleep) + "Mins"); //report sleep time
                esp_deep_sleep_start();
            }
        } else { //IF RIGHT DAY BUT NOT RIGHT HOUR
           if (timeOutHrs - 1 == timeinfo.tm_hour) {
//               Serial.println("<= 1hr before bins out");
//               Serial.println("timeOutMins: " + String(timeOutMins));
//               Serial.println("timeinfo.tm_min: " + String(timeinfo.tm_min));
               int timeToSleep = (timeOutMins - timeinfo.tm_min + 65) ; //hours mins are left till scheduled out time
               esp_sleep_enable_timer_wakeup((timeToSleep )* uS_TO_Min_FACTOR); //sleep for how many mins there are until 
//               Serial.println("Sleeping for: " + String(timeToSleep) + "Mins"); //report sleep time
               esp_deep_sleep_start();
           } else {
//               Serial.println("timeOutHrs: " + String(timeOutHrs));
//               Serial.println("timeinfo.tm_hour: " + String(timeinfo.tm_hour));
               int timeToSleep = (timeOutHrs - timeinfo.tm_hour) ; //hours there are left till scheduled out time
               esp_sleep_enable_timer_wakeup(timeToSleep * uS_TO_Hr_FACTOR); //sleep for how many hours there are until 
//               Serial.println("Sleeping for: " + String(timeToSleep) + "Hrs"); //report sleep time
               esp_deep_sleep_start();
           }
        } 
      
    }
    else if (botPos == 'o') {
        if (timeInHrs == timeinfo.tm_hour) { //if it's the right hour
            if (timeInMins <= timeinfo.tm_min) { //if it is also past the right minute
//                Serial.println("bring bot in");
                followLine();
                botPos = 'i';
                esp_sleep_enable_timer_wakeup(1 * uS_TO_Hr_FACTOR); //sleep for how many mins there are until 
//                Serial.println("Sleeping for: " + String(1) + "Hrs"); //report sleep time
                esp_deep_sleep_start();
            } else { //IF RIGHT DAY BUT NOT RIGHT Minutes
//                Serial.println("timeInMins: " + String(timeInMins));
//                Serial.println("timeinfo.tm_min: " + String(timeinfo.tm_min));
                int timeToSleep = (timeInMins - timeinfo.tm_min) ; //hours there are left till scheduled out time
                esp_sleep_enable_timer_wakeup(timeToSleep * uS_TO_Min_FACTOR); //sleep for how many mins there are until 
//                Serial.println("Sleeping for: " + String(timeToSleep) + "Mins"); //report sleep time
                esp_deep_sleep_start();
            }
        } else { //IF RIGHT DAY BUT NOT RIGHT HOURS
                if (timeInHrs - 1 == timeinfo.tm_hour) {
//                     Serial.println("timeInMins: " + String(timeInMins));
//                     Serial.println("timeinfo.tm_min: " + String(timeinfo.tm_min));
                     int timeToSleep = (timeInMins - timeinfo.tm_min) ; //hours mins are left till scheduled out time
                     esp_sleep_enable_timer_wakeup((timeToSleep + 65)* uS_TO_Min_FACTOR); //sleep for how many mins there are until 
//                     Serial.println("Sleeping for: " + String(timeToSleep + 65) + "Mins"); //report sleep time
                     esp_deep_sleep_start();
                 } else {  
//                     Serial.println("timeInHrs: " + String(timeInHrs));
//                     Serial.println("timeinfo.tm_hour: " + String(timeinfo.tm_hour));
                     int timeToSleep = (timeInHrs - timeinfo.tm_hour) ; //hours there are left till scheduled out time
                     esp_sleep_enable_timer_wakeup(timeToSleep * uS_TO_Hr_FACTOR); //sleep for how many hours there are until 
//                     Serial.println("Sleeping for: " + String(timeToSleep) + "Hrs"); //report sleep time
                     esp_deep_sleep_start();
                 }
        }
    }
}

String getPayload() {
    String payload;
    if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    
        HTTPClient http; //init HTTPClient object

        //Specify the URL of server to recieve HTTP request from
        http.begin("https://prod-20.ukwest.logic.azure.com:443/workflows/0ffd0f5c472944439ac7f736b3a67e31/triggers/manual/paths/invoke?api-version=2016-10-01&sp=%2Ftriggers%2Fmanual%2Frun&sv=1.0&sig=053uvepKWh_B08QweJ8DjZJWhkECvyoMlDT5T3LGWvM");

        int httpCode = http.GET(); //Make the request

        if (httpCode > 0) { //Check for the returning code

            payload= http.getString(); // store JSON string in String var payload using http func getString()
            // Serial.println(httpCode); // Prints HTTP code 
//            Serial.println(payload); // print JSON string             
        }
        //if there is a connection error with HTTP 
        else {
            Serial.println("Error on HTTP request");
        }
        http.end(); //Free the resources
    }
    return payload;
    delay(10000);
}


//function to deserialize the input JSON string
//JSON attributes stored in global variables
void DeserializeJSONString(char payloadIn[]) {
//    Serial.print("JSON String: \t");
//    Serial.println(payloadIn);
    //init json object 
    StaticJsonDocument<500> doc;
    //deserialize the JSON string into json object
    deserializeJson(doc, payloadIn); // parse msg
    //save JSON attr's as variables 
    bName = doc["bName"];
    id = doc["bCode"];
    goingOut = doc["day"];
    //print json attr's to serial monitor
//    Serial.println("Bin Name: " + String(bName));
//    Serial.println("Bin ID: " + String(id));
//    Serial.println("Schedule: " + String(goingOut));
}

void followLine() {
  while (1 == 1) {
      frontWheels.stopBot();
      //extra safety in checking twice, slows driving but speed is not a priority
      if (!uS.CloserThan(10)){
        //returns IR sensot values to global byte vars
        IRs.ReturnIR(leftSense, midSense, rightSense);
        delay(40);
        //sums IR sensor values
        short IR_TOTAL = leftSense + midSense + rightSense;
        //if all three sensors detect line
        if (IR_TOTAL == 3) {
          //stop robot
          frontWheels.stopBot();
          return;
        } else //if left sensor detects line
        if (leftSense == 1) {
          //turn right
          frontWheels.right();
          delay(40);
        } else //if right sensor detects line
        if (rightSense == 1) {
          //turn left
          frontWheels.left();
          delay(40);
        }
        else {
          frontWheels.forward();
          delay(40);
        }
      }
      else {
        delay(500);
      }
  }
}
