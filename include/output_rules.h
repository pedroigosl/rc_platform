#include <Arduino.h>
#include <pt.h>

void (*motors)();
void (*leds)();
void (*servos)();

uint8_t norm(uint16_t val_in, uint16_t val_min, uint16_t val_max, uint8_t thresh = motor_threshold)
{
    return (uint8_t)(thresh * ((float)(val_in - val_min) / (float)(val_max - val_min)));
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
    return (val >= 0) - (val < 0);
}

void runMotors()
{
    int str_val, thrt_val, l_thrt_val, r_thrt_val;
    int thrt_rlt = rltInput(channel_values[throttle_ch]);
    int str_rlt = rltInput(channel_values[steering_ch]);
    if (thrt_rlt > 0) // Forward
    {
        thrt_val = norm(thrt_rlt, 0, input_max - input_mid);
        str_val = (str_rlt > 0) * norm(str_rlt, 0, input_max - input_mid) + (str_rlt < 0) * norm(abs(str_rlt), 0, input_mid - input_min);
        l_thrt_val = (str_rlt < 0) * max(thrt_val - str_val, 0) + (str_rlt >= 0) * thrt_val;
        r_thrt_val = (str_rlt > 0) * max(thrt_val - str_val, 0) + (str_rlt <= 0) * thrt_val;
    }
    else if (thrt_rlt < 0) // Backward
    {
        thrt_val = norm(abs(thrt_rlt), 0, input_mid - input_min);
        str_val = (str_rlt > 0) * norm(str_rlt, 0, input_max - input_mid) + (str_rlt < 0) * norm(abs(str_rlt), 0, input_mid - input_min);
        l_thrt_val = (str_rlt < 0) * max(thrt_val - str_val, 0) + (str_rlt >= 0) * thrt_val;
        r_thrt_val = (str_rlt > 0) * max(thrt_val - str_val, 0) + (str_rlt <= 0) * thrt_val;
    }
    else // Turning in place
    {
        thrt_val = 0;
        str_val = (str_rlt > 0) * norm(str_rlt, 0, input_max - input_mid) + (str_rlt < 0) * norm(abs(str_rlt), 0, input_mid - input_min);
        l_thrt_val = getSign(str_rlt) * str_val;
        r_thrt_val = -getSign(str_rlt) * str_val;
    }
    motorL.run(getSign(thrt_rlt) * motorL.offset(l_thrt_val));
    motorR.run(getSign(thrt_rlt) * motorR.offset(r_thrt_val));
}

void runLED()
{
    if (channel_values[4] > (input_mid + deadzone))
    {
        digitalWrite(led_pin, HIGH);
    }
    else
    {
        digitalWrite(led_pin, LOW);
    }
}

void runServo()
{
    int turn_val;
    int head_abs = channel_values[head_ch]; // subtraction used to remove noise
    int head_rlt = rltInput(head_abs);
    if ((head_abs != 0) && (head_rlt != 0))
    {
        turn_val = norm(head_abs, 1000, 2000, 180);
        // head.write(turn_val);
    }
    else
    {
        turn_val = 90;
    }
    head.write(turn_val);
    // analogWrite(servo_pin, head_abs);
}

// Sets which mode each component should be run on
void setModes()
{
    if (channel_values[4] > (input_mid + deadzone))
    {
        motors = runMotors;
        leds = runLED;
        servos = runServo;
    }
    else
    {
        motors = runMotors;
        leds = runLED;
        servos = runServo;
    }
}

void runAll() // struct pt *pt)
{
    // PT_BEGIN(pt);
    motors();
    leds();
    servos();
    // PT_END(pt);
}