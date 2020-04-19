#include "Arduino.h"

//class for a left, mid and right IR sensor
class IR_Sensors {
private:
    //byte vars to store pin locations
    byte IR_L;
    byte IR_M;
    byte IR_R;
public:
    //constructor, takes byte[] for pin locations
    IR_Sensors(byte pins[]);
    //function to return all three IR sensor results
    //takes references to byte variables in the main sketch as parameters
    void ReturnIR(byte & IR_L, byte & IR_M, byte & IR_R);
};