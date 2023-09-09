/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Numbers written in their corresponding Hexadecimal address, read in reversed order
Version : 
Date    : 8/30/2023
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
#include <stdio.h>


// I2C Bus functions
#include <i2c.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define write_address_bus  160
#define read_address_bus  161

void write_eeprom(unsigned char data,unsigned int address);
unsigned char read_eeprom(unsigned int address);


// Declare your global variables here
char buffer[20];

void main(void)
{
// Declare your local variables here

unsigned char read_data, write_data;
int i;

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

for(i=0; i<=100; i++)
{
    
    write_data = 100 - i;
    write_eeprom(write_data,i);
    read_data = read_eeprom(i);
    lcd_clear();
    sprintf(buffer, "Address=0x%02X", i);
    lcd_puts(buffer);
    lcd_gotoxy(0,1);
    sprintf(buffer, "Data=%d", read_data);  
    lcd_puts(buffer);
    delay_ms(300);
}

while (1)
      {
      // Place your code here

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

