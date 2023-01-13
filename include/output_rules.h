#include <Arduino.h>

uint8_t norm255(uint16_t val_in, uint16_t val_min, uint16_t val_max)
{
    return (uint8_t)(255.0 * ((float)(val_in - val_min) / (float)(val_max - val_min)));
}

void runMotors()
{
    // motorA.setSpd(200);

    motorL.forward(200);
    // motorB.setSpd(200);
    motorR.forward(200);
}

void runLED() {}

void runServo() {}