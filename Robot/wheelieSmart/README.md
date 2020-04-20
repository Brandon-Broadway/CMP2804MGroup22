# **WheelieBin.ino**

## **The Problem**

This is a .ino file which is an arduino-compatable sketch for a line following robotics solution with Ultrasound obstruction detection, which will perform its line-following task on a schedule.
This has been developed as part of a proof-of-concept prototype for an automatic wheelie-bin solution. The whole solution consists of an android app, an Azure server and this robot-based Arduino compatable sketch.

The day on which te robot should perform it's task will be set using the WheelieSmart android app from this repository, which will be sent to an azure serve, and then the bot will pull that as a JSON string from an HTTP request.

## **Installation and Setup**

### **General setup**
To use this .ino sketch the .cpp & .h files from the "Modular Libraries" folder and the "botConfig.h" file in this repository must be installed on your system in the .../Arduino/Libraries directory. 
The "Modular Libraries" folder of this repo also includes a folder of test files to ensure these libraries are working correctly with your robot.

The wheelieBin.ino sketch should be uploaded to the ESP32 dev-module 
The wheelieBin.ino sketch is developed on an ESP32 dev-module board, therefore, you must ensure that within your Arduino-IDE you choose the right dev module by following: Arduino IDE/Tools/Boards/"ESP32 Dev Module". 

You may also need to install some of the libraries included at the top of the .ino sketch.

### **Robotics Artefact**
The sketch is written for an ESP32 dev module, this is important as the ESP32 chip has an inbuilt WiFi-chip which is used with the WiFi.h library and is essential to the solution.

This should be constructed with the following components:
	- ESP32 (Wroom) dev module
	- 1x (AR04) UltraSound module 
	- 3x (X9U7) Infrared modules
	- 2x DC Motors controlled with a (I used a l298n) H-Bridge driver
	- power supplies
	######Component Placements:
		  - UltraSound module facing forwards on the robot
		  - 3x Infrared modules on the front pointed at the floor. One in the centre, one 5cm either side.
		  - Motors and driver so that the robot can drive.


### **config.h**
The config.h file must be edited with your specific robot setup, azure server and network requirements.

The code comments and README in the repo directory should step you through this.


## **Usage**
When the previous instructions have been correctly followed, the robot artefact will function with the following characteristics whilst powered:
	-  The bot will receive the day set from the WheelieSmart android app. 
	-  On the morning of the day set bot will follow a black line line it is placed over until it reaches a t-shaped perpendicular line.
	-  The bot will perform it's task at the times set within the config.h file.
	-  The bot must be turned around bewtween "out" and "in" trips (as it would be by the perfect bin man).
	-  The ESP32 board will go into a low-power, deep-sleep mode set with a timer function called RightTime().

## **Class-Hierarchy Diagram**

        --------------   -----------------	----------------
        |  Motors.h  |	 | IR_Sensors.h  |	| UltraSound.h |
        --------------	 -----------------  ----------------
			    ^				 ^	    	    ^
                 \               |             /
                  \              |            /
                   \             |           /
                   has          has        has
                    a            a         a
                     \           |        /
                      --------------------
                      |	WheelieSmart.h   |				
                      --------------------



## **Conclusion** 
This solution contains many good individual parts and I hope that some of them may be of use to people.

If you have any questions, suggestions or issues with the contents of this directory please get in touch or make a pull request.
