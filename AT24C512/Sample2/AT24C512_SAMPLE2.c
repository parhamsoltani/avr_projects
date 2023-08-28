/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/28/2023
Author  : 
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

// I2C Bus functions
#include <i2c.h>

#include <delay.h>
#include <stdio.h>

#define EEPROM_BUS_ADDRESS 0XA0

// Declare your global variables here


unsigned char eeprom_read(unsigned char address)
 {
 unsigned char data;
 i2c_start();
 i2c_write(EEPROM_BUS_ADDRESS);
 i2c_write(address);
 i2c_start();
 i2c_write(EEPROM_BUS_ADDRESS | 1);
 data=i2c_read(0);
 i2c_stop();
 return data;
 }
 
void eeprom_write(unsigned char address,unsigned char data)
 {
 i2c_start();
 i2c_write(EEPROM_BUS_ADDRESS);
 i2c_write(address);
 i2c_write(data);
 i2c_stop();
 delay_ms(20);   // 10 ms delay to complete the write opertion
 }

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Bit-Banged I2C Bus initialization
// I2C Port: PORTC
// I2C SDA bit: 1
// I2C SCL bit: 0
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

while (1)
      {
      // Place your code here 
        i2c_init();
        DDRD=0xff;
        eeprom_write(0x00,0xAA);
        PORTD=eeprom_read(0x00);

      }
}
