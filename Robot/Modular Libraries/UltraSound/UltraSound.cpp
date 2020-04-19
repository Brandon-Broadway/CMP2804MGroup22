#include "UltraSound.h"

//constructs UltraSound object with the trig and echo pin locations passed as parameters
UltraSound::UltraSound(byte trigIn, byte echoIn) {
	//store pin location parameters
	TRIG = trigIn;
	ECHO = echoIn;
	//set trig to output pin
	pinMode(TRIG, OUTPUT);
	//set echo to input pin
	pinMode(ECHO, INPUT);
}
//function that returns distance of object in front of sensor
int UltraSound::CheckDistance() {
	//clear trig 
	digitalWrite(TRIG, LOW);
	delay(2);
	//send out high signal for 10 ms
	digitalWrite(TRIG, HIGH);
	delay(10);
	digitalWrite(TRIG, LOW);
	//Check for US reply

	long t = pulseIn(ECHO, HIGH);
	//using (speed = distance / time) with the speed of UltraSound waves
	long d = t * 0.034 / 2;

	return d;
}
//function that returns if there is an obstruction in front of the sensor closer than (parameter) d(cm)
bool UltraSound::CloserThan(int d) {
	if (CheckDistance() <= d) {
		return true;
		} 
	else 
		return false;
}