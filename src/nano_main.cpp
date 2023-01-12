#include <Arduino.h>

#include <board_profile.h>
#include <sensors.h>
#include <console.h>
#include <comms.h>

static struct pt input_pt;

void setup()
{
    pinMode(led_pin, OUTPUT);
    pinMode(extv_pin, INPUT);

    Serial.begin(baud);

    telemetry.begin();                        // Sets telemetry
    telemetry.addSensor(IBUS_MEAS_TYPE_EXTV); // Adds an external voltage sensor to telemetry output

    PT_INIT(&input_pt);
}

void loop()
{
    telemetry.run();

    getInput(&input_pt);
    channelReport();
    setSensors();

    // delay(100);
}