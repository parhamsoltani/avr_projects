/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/23/2023
Author  : 
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

// I2C Bus functions
#include <i2c.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
unsigned char input[13];
unsigned char i;

void main(void)
{
// Declare your local variables here

// Bit-Banged I2C Bus initialization
// I2C Port: PORTC
// I2C SDA bit: 1
// I2C SCL bit: 0
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);
lcd_clear();

TWAR = 0x32 << 1;
TWBR = 31;


while (1)
      {
      // Place your code here 
      /* 
        Set TWEA to 1 to Enable Acknowledge
        Wait for Receive Slave Address
      */
        TWCR = 0x44;
        while((TWCR&0x80)==0x00);
        for(i=0;i<12;i++) 
        {
        if(i==11) TWCR = 0x84;
	    else TWCR = 0xC4;
        while((TWCR&0x80)==0x00);
        input[i] = TWDR;                                  
        } 
        TWCR = 0x84;

        lcd_gotoxy(0,0);
        lcd_puts(input);
        delay_ms(1000);
        lcd_clear();


      }
}
