double voltage(int reading, double resistor_1 = r1, double resistor_2 = r2)
{
    return ((reading * 5) / ((1024 * resistor_2) / (resistor_1 + resistor_2)));
}
