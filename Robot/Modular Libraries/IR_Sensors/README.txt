                    -------------IR_Sensors.h Arduino library--------------

INTENTION:
==========

This is an Arduino compatable library for an array of three infrared light sensor
modules to be used for a line-following autonomous robotics application.

FUNCTIONS:
==========

IR_Sensors(int pins[]):
-------------------
	This is the class's constructor. It will instantiate an object of the class "IR_Sensors". The parameter should be an byte
	 array with the pin values of the signals to the driver.
		int pins[]:
		-----------
			The array should be formatted as so :
				(RIGHT_IR, MID_IR, LEFT_IR);

	The constructor passes each pin through the pinMode() function and sets them
	all to OUTPUT so that the class's functions are ready to use.

void ReturnIR(byte & l, byte & m, byte & r):
--------------------------------------------
    This function will change the variables in the main sketch referenced by the parameters
    by reading the digital signla from each of the infrared sensors.
    The results for each pin will be:
    1 - if the sensor detects the line (gets no IR reflection)
    0 - If the sensor does not detect the line (gets an IR relection)
        byte & l, byte & m, byte & r:
        -----------------------------
            This function takes references to byte variables in the line-following application's
            main sketch, one for each IR sensor.
