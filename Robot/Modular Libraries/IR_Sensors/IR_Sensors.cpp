#include "IR_Sensors.h"

//construct IR_Sensors obj
IR_Sensors::IR_Sensors(byte pins[]) {
    //stores pin locations for IR sensors
    IR_L = pins[0];
    IR_M = pins[1];
    IR_R = pins[2];
    //  sets up IR sensors as INPUT pins  
    pinMode(IR_L, INPUT);
    pinMode(IR_M, INPUT);
    pinMode(IR_R, INPUT);
}


//returns byte values (1/0) from IR_Sensors to passed ref args 
void IR_Sensors::ReturnIR(byte & l, byte & m, byte & r) {
    l = digitalRead(IR_L);
    m = digitalRead(IR_M);
    r = digitalRead(IR_R);
}
