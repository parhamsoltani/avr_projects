/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Voltmeter with ADC
Version : 
Date    : 9/9/2023
Author  : Parham Soltani 
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>
#include <stdio.h>

// Declare your global variables here
unsigned char LCD_Buffer[20];
unsigned int adc, last_adc = 0;

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
#define ADC_RESULOTION 1024
#define ADC_VREF 5.0

// function prototypes
void adc_init(void);
unsigned int read_adc(void);


void main(void)
{
// Declare your local variables here
float input_voltage;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTD Bit 0
// RD - PORTD Bit 1
// EN - PORTD Bit 2
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
adc_init();
lcd_init(16);
lcd_clear();

    while (1)
    {
        adc = read_adc();
        if (adc != last_adc) 
        {    
            lcd_clear();
            input_voltage = (float)adc * (ADC_VREF / ADC_RESULOTION);
            sprintf(LCD_Buffer, "ADC = %2u", adc);
            lcd_gotoxy(0,0);
            lcd_puts(LCD_Buffer);
            sprintf(LCD_Buffer, "INPUT_V = %.2fV", input_voltage);
            lcd_gotoxy(0,1);
            lcd_puts(LCD_Buffer);
            last_adc = adc;
        }
    }
}

// ADC initialization
void adc_init(void)
{   
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AVCC pin
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE;
// adc prescaler is set to 64
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);  
}

// Read the AD conversion result
unsigned int read_adc(void)
{
unsigned int adc_result;
unsigned char sreg_status=0;

ADMUX = ADC_VREF_TYPE;

// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);

sreg_status = SREG;
#asm("CLI")
adc_result = ADCW;
SREG = sreg_status;
return adc_result;
}