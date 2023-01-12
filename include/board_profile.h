#include <Arduino.h>

#include <pt.h>
#include <PPMReader.h>
#include <iBUSTelemetry.h>

const uint8_t led_pin = LED_BUILTIN;

const uint8_t extv_pin = A6;
const uint8_t tlm_pin = 11; // SPI enabled pin
const uint8_t ppm_pin = 2;  // Interrupt enabled pin
const uint8_t channel_amount = 10;

uint16_t channel_values[channel_amount];

const uint32_t baud = 115200;

double r1 = 30000; // Voltage sensor resistor 1
double r2 = 7500;  // Voltage sensor resistor 2

iBUSTelemetry telemetry(tlm_pin);
PPMReader ppm(ppm_pin, channel_amount);