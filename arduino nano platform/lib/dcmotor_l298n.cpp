#include "dcmotor_l298n.h"

dcMotor::dcMotor()
{
}

dcMotor::dcMotor(uint8_t pin_1, uint8_t pin_2)
{
    pin_a = pin_1;
    pin_b = pin_2;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
}

dcMotor::dcMotor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_s)
{
    pin_a = pin_1;
    pin_b = pin_2;
    pin_spd = pin_s;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_spd, OUTPUT);
}

dcMotor::dcMotor(uint8_t pin_1, uint8_t pin_2, bool inv)
{
    pin_a = pin_1;
    pin_b = pin_2;
    inverted = inv;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
}

dcMotor::dcMotor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_s, bool inv)
{
    pin_a = pin_1;
    pin_b = pin_2;
    pin_spd = pin_s;
    inverted = inv;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_spd, OUTPUT);
}

dcMotor::~dcMotor()
{
}

void dcMotor::setPins(uint8_t pin_1, uint8_t pin_2)
{
    pin_a = pin_1;
    pin_b = pin_2;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
}

void dcMotor::setPins(uint8_t pin_1, uint8_t pin_2, uint8_t pin_s)
{
    pin_a = pin_1;
    pin_b = pin_2;
    pin_spd = pin_s;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_spd, OUTPUT);
}
// speed in [0,255]
void dcMotor::setSpeed(uint8_t spd)
{
    speed = spd;
}

void dcMotor::invert()
{
    if (inverted == false)
    {
        inverted = true;
        return;
    }
    inverted = false;
}

uint8_t dcMotor::getDirPinA()
{
    return pin_a;
}

uint8_t dcMotor::getDirPinB()
{
    return pin_b;
}

uint8_t *dcMotor::getDirPins()
{
    uint8_t pins[2];
    pins[0] = pin_a;
    pins[1] = pin_b;
    return pins;
}

uint8_t dcMotor::getSpdPin()
{
    return pin_spd;
}

uint8_t dcMotor::getSpeed()
{
    return speed;
}

bool dcMotor::isInverted()
{
    return inverted;
}

void dcMotor::runForward()
{
    if (inverted == true)
    {
        pinout_a = 0;
        pinout_b = 1;
    }
    else
    {
        pinout_a = 1;
        pinout_b = 0;
    }
    pinout_s = speed;

    digitalWrite(pin_a, pinout_a);
    digitalWrite(pin_b, pinout_b);
    analogWrite(pin_spd, pinout_s);
}

void dcMotor::runBackward()
{
    if (inverted == true)
    {
        pinout_a = 1;
        pinout_b = 0;
    }
    else
    {
        pinout_a = 0;
        pinout_b = 1;
    }
    pinout_s = speed;

    digitalWrite(pin_a, pinout_a);
    digitalWrite(pin_b, pinout_b);
    analogWrite(pin_spd, pinout_s);
}

void dcMotor::stop()
{
    pinout_a = 0;
    pinout_b = 0;

    digitalWrite(pin_a, pinout_a);
    digitalWrite(pin_b, pinout_b);
}

void dcMotor::run(uint8_t mode = FORWARD)
{
    switch (mode)
    {
    case FORWARD:
        runForward();
        break;
    case BACKWARD:
        runBackward();
        break;
    }
}

void dcMotor::run(uint8_t spd, uint8_t mode = FORWARD)
{
    switch (mode)
    {
    case FORWARD:
        setSpeed(spd);
        runForward();
        break;
    case BACKWARD:
        setSpeed(spd);
        runBackward();
        break;
    }
}