#include <Arduino.h>

class dcMotor
{
    uint8_t spd = 0, pin_a, pin_b, pin_spd;
    float multiplier = 1.0; // Multiplier for balance. in interval [0.0, 1.0]

public:
    void setup(uint8_t pin_a, uint8_t pin_b, uint8_t pin_spd, float multiplier = 1.0)
    {
        this->pin_a = pin_a;
        this->pin_b = pin_b;
        this->pin_spd = pin_spd;
        pinMode(pin_a, OUTPUT);
        pinMode(pin_b, OUTPUT);
        pinMode(pin_spd, OUTPUT);

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
        digitalWrite(pin_a, HIGH);
        digitalWrite(pin_b, LOW);
        analogWrite(pin_spd, spd);
    }
    void forward(uint8_t spd)
    {
        this->spd = spd;
        forward();
    }
    void backward()
    {
        digitalWrite(pin_a, LOW);
        digitalWrite(pin_b, HIGH);
        analogWrite(pin_spd, spd);
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

    void stop()
    {
        digitalWrite(pin_a, HIGH);
        digitalWrite(pin_b, HIGH);
    }

    uint8_t offset(uint8_t input)
    {
        return (uint8_t)(multiplier * (float)input);
    }
};
