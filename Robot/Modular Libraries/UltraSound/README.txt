-------------UltraSound.h Arduino Library------------

INTENTION:
==========

This library is for sensing distance with an ultrasound sensor controlled
by an arduino compatable microcontroller.

The ultrasound sensor should have one TRIG pin and one ECHO pin.

This library can be used for multiple ultrasound sensors. If using for
multiple sensors please instantiate objects of the class for each of
the sensors and call the class functions on each object accordingly.


FUNCTIONS:
==========

UltraSound(byte trig, byte echo):
----------------------
	This is the class's constructor. It will instantiate an object of the class "Motor". The parameters should be byte type with the pin values of the trig and echo pins of the ultrasound sensor
	respectively.
		
	The constructor passes each pin through the pinMode() function and sets them to OUTPUT for TRIG and INPUT for ECHO so that the class's functions are ready to use.

int CheckDistance():
---------------------
	This function will return an integer value which represents
	the distance in cm of an object in front of the ultrasound sensor

bool CloserThan(int d):
-----------------------
	This function returns a boolean value which represents whether 
	there is an object in front of the ultrasound sensor less that 
	d(cm) away from it.
	Returns true if there is object is closer than d(cm).
	Returns false if there is no object closer than d(cm)

SETTING UP WITH ARDUINO IDE:
============================

1. Download this library
2. Copy into ...Arduino/libraries
3. (Re)start Arduino IDE
4. In Arduino IDE: sketch/include library/UltraSound
5. Done


EXAMPLE USE:
============

--------------------------SIDE NOTE------------------------- 
This arduino sketch serves no purpose but to demonstrate how
to construct and call functions on an UltraSound.h object
------------------------END SIDE NOTE-----------------------

//include UltraSound.h library
#include <UltraSound.h>

byte TRIG = 1;
byte ECHO = 2;


//Create UltraSound object called US
UltraSound US(TRIG, ECHO);

void setup() {
  //setup of ultrasound pins are handled using pinMode() funcs within library
}

void loop() {
  //check distance of closest object
  int d = US.CheckDistance();

  //do something if there is something less than 20cm in from of sensor
  if (US.CloserThan(20)) {
  //do stuff
  }

}

--PLEASE GET IN TOUCH WITH BUGS AND POSSIBLE FIXES--