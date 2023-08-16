/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/8/2023
Author  : Parham Soltani
Company : 
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32a.h>
#include <delay.h>

// Declare your global variables here
volatile unsigned int tot_overflow;
volatile unsigned int remainder_time;


// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{

      PORTC ^= (1<<0); 
      TCNT1 = remainder_time;  
      
}

//timer1's possible values for prescaler:8, 64, 256, 1024
//required delay is in ms
//suppose that the MCU's clock is 8MHz

void timer1_init(long int mcu_clock,int prescaler, float req_delay)
{
    long int timer_clock = mcu_clock/prescaler;
    float counting_time = 1000.0/timer_clock;
    float overflow_time = counting_time*65535;

    long int x = req_delay/counting_time;

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
            TCNT1 = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 8: // Prescaler 8
            TCCR1B |= (0<<CS00);
            TCCR1B |= (1<<CS01);
            TCCR1B |= (0<<CS02);
            TCNT1 = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 64: // Prescaler 64
            TCCR1B |= (1<<CS00);
            TCCR1B |= (1<<CS01);
            TCCR1B |= (0<<CS02);
            TCNT1 = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 256: // Prescaler 256
            TCCR1B |= (0<<CS00);
            TCCR1B |= (0<<CS01);
            TCCR1B |= (1<<CS02);
            TCNT1 = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        case 1024: // Prescaler 1024
            TCCR1B |= (1<<CS00);
            TCCR1B |= (0<<CS01);
            TCCR1B |= (1<<CS02);
            TCNT1 = remainder_time;
            TIMSK |= (1<<TOIE1);
            break;

        default:
            TCNT1 = remainder_time;
            TIMSK |= (1 << TOIE1);
            break;
    }

}




void main(void)
{
// Declare your local variables here 

//for bigger delays(more than 1000ms)use bigger prescaler(256 or 1024).
//for smaller delays(less than 1ms) use smaller prescaler(8 or 64).
int prescaler = 256;
float req_delay = 0.1;
long int mcu_clock = 8000000;
DDRC |= (1 << 0);

timer1_init(mcu_clock, prescaler, req_delay);

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=Out 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (1<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here
      }
}
