/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Even numbers written on AT24C512 and read from it
Version : 
Date    : 8/26/2023
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
#asm
   .equ __lcd_port=0x18 ;PORTB
#endasm
#include <lcd.h>
#asm
   .equ __i2c_port=0x15 ;PORTC
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>              
#include <stdio.h>
#include <math.h>              
#define write_address_bus  160
#define read_address_bus  161

void write_eeprom(unsigned char data,unsigned int address);
unsigned char read_eeprom(unsigned int address);
              

void main(void)
{
	unsigned char Buffer_lcd[16];
	int R,i;
	i2c_init();
	lcd_init(16);       
	for(i=0;i<100;i++) 
    write_eeprom(i*2,i);
	while (1)
	{
	    for(i=0;i<100;i++)
	    {
	        R=read_eeprom(i);
	        lcd_clear();
	        sprintf(Buffer_lcd,"Read Data= %u",R);
	        lcd_puts(Buffer_lcd);
	        delay_ms(1000);
	    }
	}
}

void write_eeprom(unsigned char data,unsigned int address)
{
   i2c_start();
   i2c_write(write_address_bus);   
   i2c_write(0x00);             //high byte address
   i2c_write(address);          //low byte address
   i2c_write(data);
   i2c_stop();
   delay_ms(10);

}                                                         
                              
unsigned char read_eeprom(unsigned int address)
{                                              
   unsigned char data_read;
   i2c_start();
   i2c_write(write_address_bus);
   i2c_write(0x00);                   //high byte address
   i2c_write(address);                //low byte address
   i2c_start();                 
   i2c_write(read_address_bus);
   data_read=i2c_read(0);
   i2c_stop();
   return data_read;

}

