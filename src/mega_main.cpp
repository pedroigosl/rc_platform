#include <Arduino.h>

#include <IBusBM.h>

#include <PPMReader.h>
#include <InterruptHandler.h>
#include <iBUSTelemetry.h>

// IBusBM IBus;

iBUSTelemetry telemetry(11); // SPI pin

int led_pin = LED_BUILTIN;

int interruptPin = 2;
int channelAmount = 10;
PPMReader ppm(interruptPin, channelAmount);

void setup()
{
    pinMode(led_pin, OUTPUT);
    /* Serial to display data */
    Serial.begin(115200);
    while (!Serial)
    {
    }

    // IBus.begin(Serial2); // Rx2/17 pin

    telemetry.begin(); // Sets telemetry

    telemetry.addSensor(IBUS_MEAS_TYPE_EXTV); // Adds an external voltage sensor to telemetry output
}

void loop()
{
    telemetry.run();
    // int val = IBus.readChannel(4);
    int val = ppm.latestValidChannelValue(5, 0);
    // Serial.println(val);
    if (val > 1000)
    {
        digitalWrite(led_pin, HIGH);
    }
    else
    {
        digitalWrite(led_pin, LOW);
    }
    telemetry.setSensorValueFP(1, float(val) / 100.0); // Sets float value to telemetry

    // delay(20);
}