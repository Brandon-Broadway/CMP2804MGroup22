-------------Motors.h Arduino Library------------

INTENTION:
==========

This library is for actuating 2 motors (1 left, 1 right) using an Arduino compatable
microcontroller and a l298n H-bridge type driver.

The driver should take 3 in signals for each motor (1 for each polarity and
1 for the enable pin to control speed variation).

This library can be used for multiple motor drivers. If using for multiple drivers
please instantiate an object of the class for each left&right pair of motors and 
call functions on each as desired.


FUNCTIONS:
==========

Motors(int pins[]):
-------------------
	This is the class's constructor. It will instantiate an object of the class "Motors". The parameter should be an byte
	 array with the pin values of the signals to the driver.
		int pins[]:
		-----------
			The array should be formatted as so :
				{LEFT_MOTOR_FORWARD, LEFT_MOTOR_REVERSE, RIGHT_MOTOR_FORWARD,
					RIGHT_MOTOR_REVERSE, RIGHT_MOTOR_ENABLE, LEFT_MOTOR_ENABLE};

	The constructor passes each pin through the pinMode() function and sets them
	all to OUTPUT so that the driving functions are ready to use.

forward():
----------
	Drives both motors forward causing movement forwards

left():
-------
	Drives left motor backward and right motor forward causing a pivot turn to
	the left

right():
--------
	Drives left motor forward and right motor backward causing a pivot turn to
	the right

reverse():
----------
	Drives both motors backward causing movement backwards

stopBot():
----------
	Sends low signals to all "in" pins causing all motors to stop
    


setSpeed(int left, int right):
------------------------------
	This function will set the speed of the left and right motors
	by setting the "duty cycle" of the pwm signal to the enable pins
	of the left and right motors.
	Parameters left & right are to be integer values between 
	0-255. they will be sent as digital signals the the enable pins
	set within the object's constructor.

SETTING UP WITH ARDUINO IDE:
============================

1. Download this library
2. Copy into <pathToArduinoDirectory>/Arduino/libraries
3. (Re)start Arduino IDE
4. In Arduino IDE: at the head of your sketch-> '#include "Motors.h"'
5. Done


EXAMPLE USE:
============

--------------------------SIDE NOTE------------------------- 
This arduino sketch serves no purpose but to demonstrate how
to construct and call functions on a Motors.h object
------------------------END SIDE NOTE-----------------------

//include Motor.h library
#include <Motors.h>

byte EN_LEFT = 1;
byte L_MOTOR = 2;
byte L_R_MOTOR = 3;
byte R_MOTOR = 4;
byte R_R_MOTOR = 5;
byte EN_RIGHT = 6;

//Store motor pin locations to an array
byte arr[] = {L_MOTOR, L_R_MOTOR, R_MOTOR, R_R_MOTOR};

//Create Motors object called drive
Motors drive(arr);

void setup() {
  //(FYI) setup of motor pins are handled using pinMode() funcs within libraries

  //set pwm signal on EN pins of l298n 
  drive.begin(); 
}

void loop() {
    //move forward for 200ms
    drive.forward(200);
    //stop
    drive.stopBot();
    //move backward for 200ms
    drive.reverse(200);
    //turn left until overwritten
    drive.left()
    //other code...
    //still turning
    //other functions or delay...

    //stop
    drive.stopBot();

}


--PLEASE GET IN TOUCH WITH BUGS AND POSSIBLE FIXES--