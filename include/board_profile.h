#include <Arduino.h>

#include <pt.h>
#include <PPMReader.h>
#include <iBUSTelemetry.h>

// #include <dcmotor_l298n.h>
#include <dcmotor_mx1508.h>

#include <Servo.h>

Servo head;

const uint32_t baud = 115200;

// dcMotorL298N motorL, motorR;
dcMotorMX1508 motorL, motorR;

// Pin setting
const uint8_t bltld_pin = LED_BUILTIN;
const uint8_t led_pin = 10;
const uint8_t servo_pin = 11;
const uint8_t extv_pin = A6;

const uint8_t tlm_pin = 12; // SPI enabled pin
const uint8_t ppm_pin = 2;  // Interrupt enabled pin

const uint8_t mL_pina = A0;
const uint8_t mL_pinb = A1;
// const uint8_t mL_pinspd = 5;

const uint8_t mR_pina = A2;
const uint8_t mR_pinb = A3;
// const uint8_t mR_pinspd = 6;

// Channel settings
const uint8_t channel_amount = 10;
uint16_t channel_values[channel_amount];

const uint16_t input_min = 1000;
const uint16_t input_mid = 1500; // Input mid point/resting value
const uint16_t input_max = 2000;
const uint16_t deadzone = 100; // Input deadzone buffer from mid point

const uint8_t steering_ch = 0;       // Steering channel
const uint8_t throttle_ch = 1;       // Throttle channel
const uint8_t motor_threshold = 200; // Motor threshold to avoid strain in interval [0,255]

const uint8_t head_ch = 3;

// Sensor constant values
const double r1 = 30000; // Voltage sensor resistor 1
const double r2 = 7500;  // Voltage sensor resistor 2

// Lib objects setting
iBUSTelemetry telemetry(tlm_pin);
PPMReader ppm(ppm_pin, channel_amount);

static struct pt input_pt;
static struct pt run_pt;

void setPins()
{
    pinMode(bltld_pin, OUTPUT);
    pinMode(led_pin, OUTPUT);
    pinMode(extv_pin, INPUT);

    head.attach(servo_pin);
    // pinMode(servo_pin, OUTPUT);

    // motorL.setup(mL_pina, mL_pinb, mL_pinspd);
    // motorR.setup(mR_pina, mR_pinb, mR_pinspd);
    motorL.setup(mL_pina, mL_pinb); //, mL_pinspd);
    motorR.setup(mR_pina, mR_pinb); //, mR_pinspd);
}

void setPointers()
{
    PT_INIT(&input_pt);
    PT_INIT(&run_pt);
}