/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : DS18B20 reciever with lcd2x16 (for both single and multiple mode)
Version : 
Date    : 8/14/2023
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

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here

char  Buffer_LCD[16];

// Standard Input/Output functions
#include <stdio.h>


interrupt[12]void Receive(void){
        gets(Buffer_LCD,16);
        lcd_gotoxy(0,0);           
        lcd_puts(Buffer_LCD);      
        lcd_gotoxy(7,0);          
        lcd_putsf("C");             
        lcd_gotoxy(0,1);            
        lcd_putsf("DS18B20 & USART");
        lcd_clear();  
}

void usart_init(void)
{
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: Off
// USART Mode: Asynchronous
// USART Baud Rate: 9600
    UCSRA=0;
    UCSRB=(1<<RXCIE) | (1<<RXEN);
    UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
    UBRRH=0x00;
    UBRRL=0x33;
}

void main(void)
{
// Declare your local variables here

#asm ("sei")
usart_init();

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
lcd_clear();  

while (1)
      {
      // Place your code here  
         
        
      }
}
