/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Reciever[recieves data from USART transmitter, saves it in AT24C512 and display its content on lcd2x16]
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
#include <twi.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Define constants for EEPROM size and chunk size
#define EEPROM_SIZE 524288 // 512 KB
#define CHUNK_SIZE 17

// Declare your global variables here
unsigned char ch;
unsigned int j=0;
unsigned int currentWriteAddress = 0;

unsigned char receivedData[20]; // Buffer to store received data
volatile unsigned int dataIndex = 0; // Index for the buffer
volatile unsigned char dataReady = 0;
unsigned char bufferSize=17; 

unsigned char at24c512_buff[130];

unsigned char read_buff[20];

// Standard Input/Output functions
#include <stdio.h>


void at24c512_write(unsigned char device_addr, unsigned int data_addr, unsigned char *buffer, unsigned char count);
void at24c512_read(unsigned char device_addr, unsigned int data_addr, unsigned char *buffer, unsigned char count);
void at24c512_read_last_chunks(unsigned char *buffer, unsigned char count);


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
    #asm("sei")

}

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
    ch = UDR; // Read the received character

    if (ch == '\n') // Check for end of data
    {
        //receivedData[dataIndex] = '\0'; // Null-terminate the string
        dataReady = 1; // Set the data ready flag
        dataIndex = 0; // Reset the index for the next data
    }
    else
    {
        if (dataIndex < sizeof(receivedData) - 1) // Check for buffer overflow
        {
            receivedData[dataIndex++] = ch; // Store the character in the buffer
        }
    }
}


void main(void)
{
// Declare your local variables here

unsigned char lastChunks[2 * CHUNK_SIZE];

usart_init();

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

twi_master_init(100); //I2C clock is set to 100kHz

    while (1)
    {
        if (dataReady)
        {                                                   
        
            unsigned int writeAddress = currentWriteAddress;
            at24c512_write(0x00, writeAddress, receivedData, bufferSize); 
            currentWriteAddress = (currentWriteAddress + CHUNK_SIZE) % EEPROM_SIZE;
            delay_ms(100); 
            

            at24c512_read_last_chunks(lastChunks, 2 * CHUNK_SIZE);
            //at24c512_read(0x00, writeAddress, read_buff, bufferSize);   
            
            // Clear the buffer
            for (j = 0; j < sizeof(receivedData); j++)
            {
                receivedData[j] = '\0';
            } 
            
            lcd_gotoxy(0, 0);
            lcd_putsf("Last 2 chunks of recieved data:");
            delay_ms(1000);
            lcd_clear();
            lcd_gotoxy(0, 0);
            lcd_puts(lastChunks); // Display the received data  
            
            dataReady = 0; // Reset the data ready flag

            delay_ms(2000);
            lcd_clear();
        }
    }   
}

void at24c512_write(unsigned char device_addr, 
                    unsigned int data_addr, 
                    unsigned char *buffer, 
                    unsigned char count)
{
    unsigned char i;
    device_addr += 0x50;
    at24c512_buff[0] = (data_addr&0xFF00)>>8;
    at24c512_buff[1] = (data_addr&0x00FF);
       
    for(i=0;i<count;i++) at24c512_buff[i+2] = buffer[i];    
    twi_master_trans(device_addr, at24c512_buff, count+2, 0, 0);
}

void at24c512_read(unsigned char device_addr, 
                    unsigned int data_addr, 
                    unsigned char *buffer, 
                    unsigned char count)
{
    device_addr += 0x50;
    at24c512_buff[0] = (data_addr&0xFF00)>>8;
    at24c512_buff[1] = (data_addr&0x00FF);
    
    twi_master_trans(device_addr, at24c512_buff, 2, buffer, count);
}


void at24c512_read_last_chunks(unsigned char *buffer, unsigned char count)
{
    // Calculate the read address for the last chunk of data
    unsigned int readAddress = (currentWriteAddress - CHUNK_SIZE) % EEPROM_SIZE;
    
    // Read the last chunk of data from the EEPROM
    at24c512_read(0x00, readAddress, buffer, count);
}