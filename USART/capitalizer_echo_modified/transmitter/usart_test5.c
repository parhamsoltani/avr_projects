/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Somewhat Echo Test
Version : 
Date    : 8/20/2023
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

#include <io.h>
#include <mega32a.h>
#include <delay.h>

// Declare your global variables here

char str[20];
unsigned char data;
unsigned int i = 0;


// Standard Input/Output functions
#include <stdio.h>
#include <inttypes.h>


void usart_init()
{
    UCSRA = 0;
	UCSRB |=  (1 << RXEN) |(1 << TXEN);/* Turn on the transmission and reception */  
	UCSRC |= (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);/* Use 8-bit character sizes */

	UBRRL = 0x33;		/* Load lower 8-bits of the baud rate */
	UBRRH = 0x00;	/* Load upper 8-bits */
}

unsigned char usart_read_char()
{
   //Wait untill a data is available
   while(!(UCSRA & (1<<RXC)));

   //Now USART has got data from host
   //and is available is buffer
   return UDR;
}


void usart_write_char(char data)
{


    if (data >= 'a' && data <+ 'z')
    {
        data += ('A' - 'a');
    }
    
    //Wait untill the transmitter is ready
    while (!(UCSRA & (1<< UDRE)));
    UDR='[';
    while (!(UCSRA & (1<< UDRE)));
    UDR = data;
    while (!(UCSRA & (1<< UDRE)));
    UDR = ']';
}

void usart_write_string(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
        while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/
	    UDR = str[j] ;	
		j++;
	}
}

void usart_write_string_modified(char *str)
{
    unsigned char j=0;
	while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/ 
    UDR='['; 
	while (str[j]!=0)		/* Send string till null */
	{
        if (str[j] >= 'a' && str[j] <+ 'z')
        {
            str[j] += ('A' - 'a');
        }

        while (! (UCSRA & (1<<UDRE)));
	    UDR= str[j];	
		j++;
	}
    while (! (UCSRA & (1<<UDRE)));	/* Wait for empty transmit buffer*/ 
    UDR=']';
      
}

void main(void)
{
// Declare your local variables here

usart_init();

//usart_write_string("\nSomewhat Echo Test: "); //you can also use putsf method

while (1)
{

    // for string input you must enter the '*' character in terminal for the start of the string.
    //then use '#' for the end of it.
    data = usart_read_char(); 
    if(data == '*')
    { 
      while(data != '#')
      {
         data = getchar();
         str[i++] = data;
      }
      str[--i] = NULL;
      usart_write_string_modified(str);
      delay_ms(400);
      i = 0;
        
    }
    else
    {
       usart_write_char(data); 
    }
    
    
 
         
}


}