#include <stdio.h>

unsigned int tot_overflow;
unsigned int remainder_time;


void reg_initializer_8bit(float mcu_clock,int prescaler, int req_delay)
{
    long int timer_clock = mcu_clock/prescaler;
    float counting_time = 1000.0/timer_clock;
    float overflow_time = counting_time*256;

    long int x = req_delay/counting_time;

    if (x > 255)
    {
        tot_overflow += (req_delay/overflow_time);
        float remaining_time = req_delay - overflow_time*tot_overflow;
        long int remaining_counts = remaining_time/counting_time;
        remainder_time = 255 - remaining_counts;
    }
    else
    {
        remainder_time = 255 - x;
    }

}

int main() {
    int prescaler = 1024;
    int req_delay = 1000;
    float mcu_clock = 8000000.0;

    reg_initializer_8bit(mcu_clock,prescaler, req_delay);

    printf("Hexadecimal value of y: %X\n", remainder_time);
    printf("number of overflow: %d\n", tot_overflow);

    return 0;
}
