#include <Arduino.h>

#include <board_profile.h>
#include <sensors.h>
#include <console.h>
#include <comms.h>
// #include <dcmotor_l298n.h>
#include <output_rules.h>

// dcMotor motorA, motorB;
static struct pt input_pt;

void setup()
{
    // pinMode(led_pin, OUTPUT);
    // pinMode(extv_pin, INPUT);
    setPins();

    // motorA.setup(mA_pina, mA_pinb);
    // motorB.setup(mB_pina, mB_pinb);

    Serial.begin(baud);

    setTelemetry();
    // telemetry.begin();                        // Sets telemetry
    // telemetry.addSensor(IBUS_MEAS_TYPE_EXTV); // Adds an external voltage sensor to telemetry output

    PT_INIT(&input_pt);
    // motorA.setSpd(200);
    // motorA.forward();
}

void loop()
{
    runTelemetry();
    getInput(&input_pt);
    runMotors();
    // channelReport();

    // delay(100);
}