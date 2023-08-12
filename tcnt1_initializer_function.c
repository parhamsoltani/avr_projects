#include <stdio.h>


unsigned int tot_overflow;
unsigned int remainder_time;

void reg_initializer_16(float mcu_clock,int prescaler, int req_delay)
{
    long int timer_clock = mcu_clock/prescaler;
    float counting_time = 1000.0/timer_clock;
    float overflow_time = counting_time*65535;

    int x = req_delay/counting_time;

    unsigned int y = 0;
    if (x > 65535)
    {
        tot_overflow += (x/65535);
        remainder_time = 65536 - ((unsigned int)x%65535);
    }
    else
    {
        remainder_time = 65535 - x;
    }

}

int main() {
    int prescaler = 256;
    int req_delay = 1000;
    float mcu_clock = 8000000.0;

    reg_initializer_16(mcu_clock, prescaler, req_delay);

    printf("Hexadecimal value of y: %X\n", remainder_time);
    printf("number of overflow: %d\n", tot_overflow);

    return 0;
}
