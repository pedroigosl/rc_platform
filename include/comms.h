#include <Arduino.h>
#include <pt.h>

/******************************************
                TELEMETRY
******************************************/

void setSensors()
{
    telemetry.setSensorValueFP(1, voltage(analogRead(extv_pin))); // Sets external voltage sensor to telemetry
}

void setTelemetry()
{
    telemetry.begin();                        // Sets telemetry
    telemetry.addSensor(IBUS_MEAS_TYPE_EXTV); // Adds an external voltage sensor to telemetry output
}

void runTelemetry()
{
    telemetry.run();
    setSensors();
}

/******************************************
            CHANNELS' INPUT
******************************************/

void getInput(struct pt *pt)
{
    // static unsigned long timestamp = 0;
    PT_BEGIN(pt);
    for (int channel = 1; channel <= channel_amount; ++channel)
    {

        channel_values[channel - 1] = ppm.latestValidChannelValue(channel, 1500);
    }
    // PT_WAIT_UNTIL(pt, millis() - timestamp > 1000);
    PT_END(pt);
}