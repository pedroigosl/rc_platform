#ifndef DCMOTOR_L298N_H
#define DCMOTOR_L298N_H

#include "Arduino.h"

class dcMotor
{
public:
    dcMotor(uint8_t motorNum);
    void run(uint8_t, uint8_t);
    void setTurning(uint8_t);
    void setSpeed(uint8_t);

private:
    uint8_t motorNum;
};

#endif
