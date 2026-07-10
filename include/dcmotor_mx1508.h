#include <Arduino.h>

class dcMotorMX1508
{
    uint8_t spd = 0, pin_a, pin_b;
    int raw_spd;
    float multiplier = 1.0; // Multiplier for balance. in interval [0.0, 1.0]

public:
    void setup(uint8_t pin_a, uint8_t pin_b, float multiplier = 0.5) // 1.0)
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

    void setMultiplier(float multiplier)
    {
        this->multiplier = multiplier;
    }

    int getSpd()
    {
        return raw_spd;
    }

    void forward()
    {
        analogWrite(pin_a, spd);
        analogWrite(pin_b, 0);
    }
    void forward(uint8_t spd)
    {
        this->spd = spd;
        forward();
    }
    void backward()
    {
        analogWrite(pin_a, 0);
        analogWrite(pin_b, spd);
    }

    void backward(uint8_t spd)
    {
        this->spd = spd;
        backward();
    }

    void run(int spd)
    {
        this->raw_spd = spd;
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
        analogWrite(pin_a, 0);
        analogWrite(pin_b, 0);
    }

    void brake()
    {
        analogWrite(pin_a, 255);
        analogWrite(pin_b, 255);
    }

    int offset(int input)
    {
        return (int)(multiplier * (float)input);
    }
};
