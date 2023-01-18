#include <Arduino.h>

#include <board_profile.h>
#include <sensors.h>
#include <console.h>
#include <comms.h>

#include <output_rules.h>

// static struct pt input_pt;

void setup()
{

    setPins();

    Serial.begin(baud);

    setTelemetry();

    setPointers();
    // PT_INIT(&input_pt);
}

void loop()
{
    runTelemetry();
    getInput(&input_pt);
    setModes();
    runAll(); //&run_pt);

    channelReport();
    // speedReport();
}