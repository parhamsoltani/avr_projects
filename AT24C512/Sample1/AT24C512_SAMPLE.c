/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : AT24C512 sample
Version : 
Date    : 8/28/2023
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
#include <at24c512.h>
#include <twi.h>

#include <i2c.h>

// Declare your global variables here

unsigned char write_buff[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
unsigned char read_buff[10];
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

twi_master_init(100);
DDRD = 0xFF;
 
at24c512_write(0x00, 0x0000, write_buff, 10);
delay_ms(100);
at24c512_read(0x00, 0x0000, read_buff, 10);
 
    for(i=0;i<10;i++)
    {
    PORTD = read_buff[i];
    delay_ms(500);    
    }


while (1)
      {
      // Place your code here

      }
}
