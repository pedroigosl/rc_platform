#include <Arduino.h>

void (*motors)();
void (*leds)();
void (*servos)();

uint8_t norm(uint16_t val_in, uint16_t val_min, uint16_t val_max)
{
    return (uint8_t)(motor_threshold * ((float)(val_in - val_min) / (float)(val_max - val_min)));
}

// Input relative to mid value
int rltInput(uint16_t val_in)
{
    if (val_in <= (input_mid - deadzone))
    {
        return (val_in - input_mid);
    }
    if (val_in >= (input_mid + deadzone))
    {
        return (val_in - input_mid);
    }

    return 0; // Value in deadzone, should be thrown
}

int getSign(int val)
{
    return (val > 0) - (val < 0);
}

void runMotors()
{
    uint8_t str_val, thrt_val, l_thrt_val, r_thrt_val;
    int thrt_rlt = rltInput(channel_values[throttle_ch]);
    int str_rlt = rltInput(channel_values[steering_ch]);
    if (thrt_rlt >= 0)
    {
        thrt_val = norm(thrt_rlt, 0, input_max - input_mid);
        str_val = (str_rlt > 0) * norm(str_rlt, 0, input_max - input_mid) + (str_rlt < 0) * norm(abs(str_rlt), 0, input_mid - input_min);
        l_thrt_val = (str_rlt < 0) * max(thrt_val - str_val, 0) + (str_rlt >= 0) * thrt_val;
        r_thrt_val = (str_rlt > 0) * max(thrt_val - str_val, 0) + (str_rlt <= 0) * thrt_val;
    }
    else
    {
        thrt_val = norm(abs(thrt_rlt), 0, input_mid - input_min);
        str_val = (str_rlt > 0) * norm(str_rlt, 0, input_max - input_mid) + (str_rlt < 0) * norm(abs(str_rlt), 0, input_mid - input_min);
        l_thrt_val = (str_rlt < 0) * max(thrt_val - str_val, 0) + (str_rlt >= 0) * thrt_val;
        r_thrt_val = (str_rlt > 0) * max(thrt_val - str_val, 0) + (str_rlt <= 0) * thrt_val;
    }
    motorL.run(getSign(thrt_rlt) * motorL.offset(l_thrt_val));
    motorR.run(getSign(thrt_rlt) * motorR.offset(r_thrt_val));
}

void runCrazyMotors()
{
    uint8_t str_val, thrt_val;
    // motorA.setSpd(200);
    // if ()

    motorL.forward(motorL.offset(0));
    // motorB.setSpd(200);
    // motorR.forward(200);
}

void runLED() {}

void runServo() {}

// Sets which mode each component should be run on
void setModes()
{
    if (channel_values[4] > (input_mid + deadzone))
    {
        motors = runCrazyMotors;
        leds = runLED;
    }
    else
    {
        motors = runMotors;
        // leds = runLED;
    }
}

void runAll()
{
    motors();
    // leds();
    // servos();
}