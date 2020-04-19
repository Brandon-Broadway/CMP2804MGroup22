#pragma once
#include <Arduino.h>

class UltraSound
{
public:
	UltraSound(byte trig, byte echo);
	//returns distance of obstruction in front of US sensor
	int CheckDistance();
	//checks if there is something xinfront of the US sensor closer than d(cm)
	bool CloserThan(int d);
private:
	//storage for pin locations
	byte TRIG, ECHO;
};

