/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/22/2023
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

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
unsigned char str[20];
unsigned char ch;
unsigned int i = 0, j=0;

// Standard Input/Output functions
#include <stdio.h>

void usart_init()
{

    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: Off
    // USART Mode: Asynchronous
    // USART Baud Rate: 9600
    UCSRA=0x00;
    UCSRB=(1<<RXCIE) | (1<<RXEN);
    UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
    UBRRH=0x00;
    UBRRL=0x33;

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
usart_init();


while (1)
{
    lcd_gotoxy(0, 0);
    lcd_putsf("Echo test:\t");
    
    i = 0; // Reset index for the string
    while (1)
    { 
        while(!(UCSRA & (1<<RXC)));
        ch = UDR;
        
        if (ch == ']')
        {   
            str[i++] = ch;
            break; // Exit the loop when closing bracket is received
        }
        
        str[i++] = ch;
    }
    
    // Display and clear the received string
    lcd_gotoxy(0, 1);
    lcd_puts(str);
    delay_ms(5000);
    lcd_clear();
    
    // Clear the string array for next input
    for (j = 0; j < sizeof(str); j++)
    {
        str[j] = '\0';
    }
}

}

