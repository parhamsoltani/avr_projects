/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : MQ135 sensor
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
#include <stdio.h>

#include <delay.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here

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

void adc_init()
{
// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
}

void mq135_init()
{
      float i;
      int MQ135;
      i=read_adc(0);                
      MQ135=(i*100)/1023 ;                    
      sprintf(Buffer_lcd,"Gas amount=%d",MQ135);

}

void main(void)
{
// Declare your local variables here




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
// Characters/line: 16
lcd_init(16);
adc_init();

while (1)
      {
      // Place your code here 
      mq135_init();  
      lcd_gotoxy(0,0);                   
      lcd_puts(Buffer_lcd);                    
      lcd_putsf("%");                    
      delay_ms(500);                   
      lcd_clear(); 

      }
}
