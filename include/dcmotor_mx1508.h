#include <Arduino.h>

class dcMotorMX1508
{
    uint8_t spd = 0, pin_a, pin_b;
    float multiplier = 1.0; // Multiplier for balance. in interval [0.0, 1.0]

public:
    void setup(uint8_t pin_a, uint8_t pin_b, float multiplier = 1.0)
    {
        this->pin_a = pin_a;
        this->pin_b = pin_b;
        pinMode(pin_a, OUTPUT);
        pinMode(pin_b, OUTPUT);

        this->multiplier = multiplier;
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
        this->spd = spd;
        forward();
    }
    void backward()
    {
        digitalWrite(pin_a, LOW);
        analogWrite(pin_b, spd);
    }

    void backward(uint8_t spd)
    {
        this->spd = spd;
        backward();
    }

    void run(int spd)
    {
        if (spd >= 0)
        {
            forward((uint8_t)spd);
        }
        else
        {
            backward((uint8_t)abs(spd));
        }
    }

    void off()
    {
        digitalWrite(pin_a, LOW);
        digitalWrite(pin_b, LOW);
    }

    void brake()
    {
        digitalWrite(pin_a, HIGH);
        digitalWrite(pin_b, HIGH);
    }

    int offset(int input)
    {
        return (int)(multiplier * (float)input);
    }
};
