#include <Arduino.h>

void channelReport()
{
    for (int channel = 1; channel <= channel_amount; ++channel)
    {
        Serial.print("ch");
        Serial.print(channel);
        Serial.print(": ");
        Serial.print(channel_values[channel - 1]);
        Serial.print("\t");
    }
    Serial.println();
}

void speedReport()
{
    Serial.print(motorL.getSpd());
    Serial.print("\t");
    Serial.println(motorR.getSpd());
}

void modeReport()
{
}
