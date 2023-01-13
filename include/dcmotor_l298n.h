#include <Arduino.h>

class dcMotor
{
    uint8_t spd = 0, pin_a, pin_b;

public:
    void setup(uint8_t pin_a, uint8_t pin_b)
    {
        this->pin_a = pin_a;
        this->pin_b = pin_b;
        pinMode(pin_a, OUTPUT);
        pinMode(pin_b, OUTPUT);
    }

    void setSpd(uint8_t spd)
    {
        this->spd = spd;
    }

    uint8_t getSpd()
    {
        return spd;
    }

    void forward()
    {
        analogWrite(pin_a, spd);
        digitalWrite(pin_b, LOW);
    }
    void forward(uint8_t spd)
    {
        analogWrite(pin_a, spd);
        digitalWrite(pin_b, LOW);
    }
    void backward()
    {
        digitalWrite(pin_a, LOW);
        analogWrite(pin_b, spd);
    }

    void backward(uint8_t spd)
    {
        digitalWrite(pin_a, LOW);
        analogWrite(pin_b, spd);
    }

    void off()
    {
        digitalWrite(pin_a, LOW);
        digitalWrite(pin_b, LOW);
    }
};
