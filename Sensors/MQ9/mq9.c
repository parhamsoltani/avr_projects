/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : MQ9 gas sensor 
Version : 
Date    : 8/19/2023
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
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here

float i;
int MQ9;
unsigned char Buffer_lcd[16];

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}


void adc_init(unsigned char prescaler)
{
    // ADC initialization
    // ADC Clock frequency: 1000.000 kHz
    // ADC Voltage Reference: AREF pin
    // ADC Auto Trigger Source: ADC Stopped

    ADMUX = ADC_VREF_TYPE;
    ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE);  
    
    //default MCU clock frequency is considered 8MHz.
    //for 1000.000 kHz ADC frequency, prescaler 64 is used with ADPS registers.
    
    switch (prescaler)
    {
        case 2:
            ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);
            break;
        case 4:
            ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
            break;
        case 8:
            ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
            break;
        case 16:
            ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0);
            break;
        case 32:
            ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);
            break;
        case 64:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
            break;
        case 128:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
            break;
        default:
            // Default to prescaler 64
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
            break;
    }

    SFIOR = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);
}

void mq9_init(void)
{
i=read_adc(0);                   
MQ9=(i*100)/1023 ;                 
sprintf(Buffer_lcd,"Gas amount: %d",MQ9);
lcd_gotoxy(0,0);  
lcd_puts(Buffer_lcd);                     
lcd_putsf("%");                   
delay_ms(500);                     
lcd_clear(); 
}



void main(void)
{
// Declare your local variables here


// Input/Output Ports initialization
// Port A initialization
DDRA= (0<<DDA0);
PORTA= (0<<PORTA0);


// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 8
lcd_init(16);
adc_init(64);

while (1)
      {
      // Place your code here   
      mq9_init();

      }
}
