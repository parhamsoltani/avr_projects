/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
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

// Declare your global variables here

// Standard Input/Output functions
#include <stdio.h>

#define F_CPU 8000000UL			/* Define frequency here its 8MHz */

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

interrupt [USART_RXC] void usart_rx_isr(void)
{
    PORTA=UDR;
}

void usart_init(long USART_BAUDRATE)
{
// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600

UCSRB=(1<<RXCIE) | (1<<RXEN) | (1<<TXEN);
UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);

UBRRL = BAUD_PRESCALE;		/* Load lower 8-bits of the baud rate */
UBRRH = (BAUD_PRESCALE >> 8);

}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
DDRA=(1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
PORTA=(0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
DDRB=(0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0); 
PORTB=(1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);



usart_init(51);
#asm("sei");

while (1)
      {
      // Place your code here 
      UDR=PINB;
      while(!(UCSRA & (1<<UDRE)));

      }
}
