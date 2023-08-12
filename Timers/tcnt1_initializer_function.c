#include <stdio.h>


unsigned int tot_overflow;
unsigned int remainder_time;

void reg_initializer_16(long int mcu_clock,int prescaler, int req_delay)
{
    long int timer_clock = mcu_clock/prescaler;
    float counting_time = 1000.0/timer_clock;
    float overflow_time = counting_time*65535;

    int x = req_delay/counting_time;


    if (x > 65535)
    {
        tot_overflow += (x/65535);
        remainder_time = 65536 - ((unsigned int)x%65535);
    }
    else
    {
        remainder_time = 65535 - x;
    }

    switch (prescaler)
    {
        case 1: // No prescaling
            TCCR1B |= (1<<CS00);
            TCCR1B |= (0<<CS01);
            TCCR1B |= (0<<CS02);
            TCNT1B = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 8: // Prescaler 8
            TCCR1B |= (0<<CS00);
            TCCR1B |= (1<<CS01);
            TCCR1B |= (0<<CS02);
            TCNT1B = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 64: // Prescaler 64
            TCCR1B |= (1<<CS00);
            TCCR1B |= (1<<CS01);
            TCCR1B |= (0<<CS02);
            TCNT1B = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 256: // Prescaler 256
            TCCR1B |= (0<<CS00);
            TCCR1B |= (0<<CS01);
            TCCR1B |= (1<<CS02);
            TCNT1B = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 1024: // Prescaler 1024
            TCCR1B |= (1<<CS00);
            TCCR1B |= (0<<CS01);
            TCCR1B |= (1<<CS02);
            TCNT1B = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        default:
            TCNT1 = remainder_time;
            TIMSK |= (1 << TOIE1);
            break;
    }

}

int main() {
    int prescaler = 256;
    int req_delay = 1000;
    long int mcu_clock = 8000000;

    reg_initializer_16(mcu_clock, prescaler, req_delay);

    printf("Hexadecimal value of y: %X\n", remainder_time);
    printf("number of overflow: %d\n", tot_overflow);

    return 0;
}
