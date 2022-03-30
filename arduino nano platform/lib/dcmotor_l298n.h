#ifndef DCMOTOR_L298N_H
#define DCMOTOR_L298N_H

#include "Arduino.h"

class dcMotor
{
public:
    dcMotor();
    // Sets a dcMotor and pins for direction
    dcMotor(uint8_t pin_1, uint8_t pin_2);
    // Sets a dcMotor, pins for direction and pin for speed
    dcMotor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_s);
    // If inverted true, inverts motor output
    dcMotor(uint8_t pin_1, uint8_t pin_2, bool inv);
    // If inverted true, inverts motor output
    dcMotor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_s, bool inv);
    // destructor
    ~dcMotor();
    // sets direction pins for motor
    void setPins(uint8_t pin_1, uint8_t pin_2);
    // sets direction and speed pins for motor
    void setPins(uint8_t pin_1, uint8_t pin_2, uint8_t pin_s);
    // sets motor speed;
    void setSpeed(uint8_t spd);
    // return direction pin a
    uint8_t getDirPinA();
    // return direction pin b
    uint8_t getDirPinB();
    // return direction pin numbers
    uint8_t *getDirPins();
    // return speed pin number
    uint8_t getSpdPin();
    // return speed value
    uint8_t getSpeed();
    // return whether is inverted
    bool isInverted();
    // sets INa = 1 and INb = 0
    void runForward();
    // sets INa = 0 and INb = 1
    void runBackward();
    // sets all IN pins to 0
    void stop();

private:
    uint8_t pin_a, pin_b;               // direction pins
    uint8_t pin_spd;                    // speed pin
    uint8_t speed = 0;                  // speed value
    uint8_t pinout_a = 0, pinout_b = 0; // direction pins outputs
    uint8_t pinout_s = 0;               // speed pin output
    bool inverted = false;              // whether to change motor direction
};

#endif
