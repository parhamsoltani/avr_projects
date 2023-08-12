#include <stdio.h>

unsigned int tot_overflow;
unsigned int remainder_time;


//CS registers in Timer0 (CS00, CS01, CS02) obtain 8 modes for clock sources.
//In timer0_init function only 5 modes are supported.
//prescaler=1 --> No prescaler (CS=001)
//prescaler=8 --> CLKI/O /8 (CS=010)
//prescaler=64 --> CLKI/O /64 (CS=011)
//prescaler=256 --> CLKI/O /256 (CS=100)
//prescaler=1024 --> CLKI/O /1024 (CS=101)

void timer0_init(long int mcu_clock,int prescaler, int req_delay)
{
    long int timer_clock;
    float counting_time;
    float overflow_time;
    long int x;
    float remaining_time;
    long int remaining_counts;    
    
    switch (prescaler)
    {
        case 1: // No prescaling
            TCCR0 |= (1<<CS00);
            TCCR0 |= (0<<CS01);
            TCCR0 |= (0<<CS02);
            TCNT0=0x00;
            TIMSK |= (1<<TOIE0);
            counter_overflow = 0; 
            break;
        
        case 8: // Prescaler 8
            TCCR0 |= (0<<CS00);
            TCCR0 |= (1<<CS01);
            TCCR0 |= (0<<CS02);
            TCNT0=0x00;
            TIMSK |= (1<<TOIE0);
            counter_overflow = 0; 
            break;

        case 64: // Prescaler 64
            TCCR0 |= (1<<CS00);
            TCCR0 |= (1<<CS01);
            TCCR0 |= (0<<CS02);
            TCNT0=0x00;
            TIMSK |= (1<<TOIE0);
            counter_overflow = 0; 
            break;

        case 256: // Prescaler 256
            TCCR0 |= (0<<CS00);
            TCCR0 |= (0<<CS01);
            TCCR0 |= (1<<CS02);
            TCNT0=0x00;
            TIMSK |= (1<<TOIE0);
            counter_overflow = 0; 
            break;

        case 1024: // Prescaler 1024
            TCCR0 |= (1<<CS00); 
            TCCR0 |= (0<<CS01);
            TCCR0 |= (1<<CS02);
            TCNT0=0x00;
            TIMSK |= (1<<TOIE0);
            counter_overflow = 0; 
            break;

        default:
            TCNT0=0x00;
            TIMSK |= (1<<TOIE0);
            counter_overflow = 0;
            break;
    }


    timer_clock = mcu_clock/prescaler;
    counting_time = 1000.0/timer_clock;
    
    overflow_time = counting_time*256;
    x = req_delay/counting_time;

    if (req_delay >= overflow_time)
    {
        tot_overflow = (req_delay/overflow_time);
        remaining_time = req_delay - overflow_time*tot_overflow;
        remaining_counts = remaining_time/counting_time;
        remainder_time = 255 - remaining_counts;
    }
    else
    {
        tot_overflow=0;
        remainder_time = 255 - x; 
        TCNT0=remainder_time;
    }


}


int main() {
    int prescaler = 1024;
    int req_delay = 1000;
    long int mcu_clock = 8000000;

    reg_initializer_8bit(mcu_clock,prescaler, req_delay);

    printf("Hexadecimal value of y: %X\n", remainder_time);
    printf("number of overflow: %d\n", tot_overflow);

    return 0;
}
