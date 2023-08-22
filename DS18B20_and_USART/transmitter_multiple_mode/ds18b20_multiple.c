/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :  Multiple DS18B20 sensors with USART (Transmitter)
Version : 
Date    : 8/16/2023
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

// 1 Wire Bus interface functions
#include <1wire.h>

// DS1820 Temperature Sensor functions
#include <ds18B20.h>

// maximum number of DS1820 devices
// connected to the 1 Wire bus
#define MAX_DS1820 8
// number of DS1820 devices
// connected to the 1 Wire bus
unsigned char ds18b20_devices;
// DS1820 devices ROM code storage area,
// 9 bytes are used for each device
// (see the w1_search function description in the help)
unsigned char ds1820_rom_codes[MAX_DS1820][9];

// Declare your global variables here

float Temperature[8]={0,0,0,0,0,0,0,0};  //temperature for each sensor is stored here
char  Buffer_LCD[16];
unsigned char i;

// Standard Input/Output functions
#include <stdio.h>


void usart_init(void)
{
    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: Off
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud Rate: 9600
    UCSRA=0;
    UCSRB=(1<<TXEN);
    UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
    UBRRH=0x00;
    UBRRL=0x33;
}


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Function: Bit1=In 
DDRB= (0<<DDB1);
// State: Bit1=T 
PORTB=(1<<PORTB1);  //internal pull-up is enabled.


// 1 Wire Bus initialization
// 1 Wire Data port: PORTB
// 1 Wire Data bit: 0
// Note: 1 Wire port settings are specified in the
// Project|Configure|C Compiler|Libraries|1 Wire menu.
w1_init();

// Determine the number of DS1820 devices
// connected to the 1 Wire bus
ds18b20_devices=w1_search(0xf0,ds1820_rom_codes);

usart_init();
while (1)
      {
      // Place your code here
      if(PINB.1 == 0)
      {
        
        Temperature[i] = ds18b20_temperature(ds1820_rom_codes[i]);
        sprintf(Buffer_LCD,"T%01d=%4.2f",i+1,Temperature[i]); 
        puts(Buffer_LCD);
        delay_ms(250);
        if(i<7) i++;
        else if(i==7) i=0;
      }


      }
}




