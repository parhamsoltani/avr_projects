/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Interfacing BMP280 by i2C
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
#include <stdio.h>
#include <stdlib.h>

// I2C Bus functions
#include <i2c.h>

// Alphanumeric LCD functions
#include <alcd.h>

#define BMP280_I2C_ADDRESS  0xEC
#include <BMP280_Lib.c>


// Declare your global variables here

unsigned char Buffer_lcd[16];
int32_t temperature;
uint32_t pressure;

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
// RS - PORTD Bit 0
// RD - PORTD Bit 1
// EN - PORTD Bit 2
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
lcd_init(16);

// initialize the BMP280 sensor
if(BMP280_begin() == 0)
{  // connection error or device address wrong!
    lcd_gotoxy(0, 0);   
    lcd_puts("Connection");
    lcd_gotoxy(0, 1);   
    lcd_puts("error!");
    while(1);  // stay here
}
	
lcd_gotoxy(0, 1);    
lcd_puts("Temp:");
lcd_gotoxy(0, 0);    
lcd_puts("Pres:");

while (1)
      {
      // Place your code here  
      // Read temperature (in hundredths C) and pressure (in Pa)
      // Values from BMP280 sensor
      BMP280_readTemperature(&temperature);  // Reading temperature
      BMP280_readPressure(&pressure);        // Reading pressure
       
      // Print data on the LCD screen
      //Temperature 
      lcd_gotoxy(5, 1);    
      if(temperature < 0)
      {
        lcd_putchar('-');
        temperature = abs(temperature);
      }
      else
      lcd_putchar(' ');
       
      sprintf(Buffer_lcd, "%02u.%02u%cC", temperature / 100, temperature % 100, 223);
	  lcd_puts(Buffer_lcd);

      //Pressure 
      lcd_gotoxy(6, 0);    
      sprintf(Buffer_lcd, "%04u.%02uhPa", pressure/100, pressure % 100);
      lcd_puts(Buffer_lcd);

      delay_ms(2000);  // wait 2 seconds

      }
}








