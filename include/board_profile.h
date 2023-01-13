#include <Arduino.h>

#include <pt.h>
#include <PPMReader.h>
#include <iBUSTelemetry.h>

#include <dcmotor_l298n.h>

dcMotor motorL, motorR;

// Pin setting
const uint8_t bltld_pin = LED_BUILTIN;
const uint8_t led_pin = 10;
const uint8_t servo_pin = 9;
const uint8_t extv_pin = A6;

const uint8_t tlm_pin = 11; // SPI enabled pin
const uint8_t ppm_pin = 2;  // Interrupt enabled pin

const uint8_t mL_pina = A1;
const uint8_t mL_pinb = A2;
const uint8_t mR_pina = A3;
const uint8_t mR_pinb = A4;

// Channel setting
const uint8_t channel_amount = 10;
uint16_t channel_values[channel_amount];

// Input buffer
const uint16_t input_mid = 1500;
const uint16_t input_buffer = 50;

const uint32_t baud = 115200;

// Sensor constant values
const double r1 = 30000; // Voltage sensor resistor 1
const double r2 = 7500;  // Voltage sensor resistor 2

// Lib objects setting
iBUSTelemetry telemetry(tlm_pin);
PPMReader ppm(ppm_pin, channel_amount);

void setPins()
{
    pinMode(bltld_pin, OUTPUT);
    pinMode(led_pin, OUTPUT);
    pinMode(extv_pin, INPUT);

    motorL.setup(mL_pina, mL_pinb);
    motorR.setup(mR_pina, mR_pinb);
}