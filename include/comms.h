#include <Arduino.h>
#include <pt.h>

void setSensors()
{
    telemetry.setSensorValueFP(1, 10.0); // voltage(extv_pin)); // Sets external voltage sensor to telemetry
}

void getInput(struct pt *pt)
{
    PT_BEGIN(pt);
    for (int channel = 1; channel <= channel_amount; ++channel)
    {

        channel_values[channel - 1] = ppm.latestValidChannelValue(channel, 1500);
    }
    PT_END(pt);
}