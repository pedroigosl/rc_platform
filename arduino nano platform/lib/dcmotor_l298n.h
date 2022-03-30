#ifndef DCMOTOR_L298N_H
#define DCMOTOR_L298N_H

#include "Arduino.h"

class dcMotor
{
public:
    // Sets a dcMotor and pins for direction
    dcMotor(uint8_t motor_num, uint8_t pin_a, uint8_t pin_b);
    // Sets a dcMotor, pins for direction and pin for speed
    dcMotor(uint8_t motor_num, uint8_t pin_a, uint8_t pin_b, uint8_t pin_s);
    // If inverted true, inverts motor output
    dcMotor(uint8_t motor_num, uint8_t pin_a, uint8_t pin_b, bool inverted);
    // If inverted true, inverts motor output
    dcMotor(uint8_t motor_num, uint8_t pin_a, uint8_t pin_b, uint8_t pin_s, bool inverted);
    // destructor
    ~dcMotor();
    // sets INa = 1 and INb = 0
    void runForward();
    // sets INa = 0 and INb = 1
    void runBackward();
    // sets all IN pins to 0
    void stop();
    // updates motor number
    void setMotor(uint8_t motor_num);
    // sets direction pins for motor
    void setPins(uint8_t pin_a, uint8_t pin_b);
    // sets direction and speed pins for motor
    void setPins(uint8_t pin_a, uint8_t pin_b, uint8_t pin_s);
    void setTurning(uint8_t);
    void setSpeed(uint8_t);
    uint8_t getNum();
    uint8_t getDirPins();
    uint8_t getSpdPin();
    uint8_t getSpeed();
    bool isInverted();

private:
    uint8_t motor_num;
    uint8_t pin_a, pin_b; // direction pins
    uint8_t pin_s;        // speed pin
    uint8_t speed = 0;
    uint8_t pinout_a = 0, pinout_b = 0; // direction pins outputs
    // TO CHECK. THE PIN IS PWM, SO 0 IS ACTUALLY MOVING BACKWARD
    uint8_t pinout_s = 0;  // speed pin output
    bool inverted = false; // whether to change motor direction
};

#endif
