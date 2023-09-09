/*******************************************************
Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8/000000 MHz
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

char lcd[16];
int32_t temperature;
uint32_t pressure;
float i;
int MQ9;



// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}


void adc_init(unsigned char prescaler)
{
    // ADC initialization
    // ADC Clock frequency: 1000.000 kHz
    // ADC Voltage Reference: AREF pin
    // ADC Auto Trigger Source: ADC Stopped

    ADMUX = ADC_VREF_TYPE;
    ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE);  
    
    //default MCU clock frequency is considered 8MHz.
    //for 1000.000 kHz ADC frequency, prescaler 64 is used with ADPS registers.
    
    switch (prescaler)
    {
        case 2:
            ADCSRA |= (0 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);
            break;
        case 4:
            ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
            break;
        case 8:
            ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
            break;
        case 16:
            ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0);
            break;
        case 32:
            ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0);
            break;
        case 64:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
            break;
        case 128:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
            break;
        default:
            // Default to prescaler 64
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
            break;
    }

    SFIOR = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);
}



void usart_init()
{
 // USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0;
UCSRB= (1<<TXEN) ;
UCSRC=(1<<URSEL)| (1<<UCSZ1) | (1<<UCSZ0);
UBRRH=0x00;
UBRRL=0x33;
}


void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
DDRA= (0<<DDA0);
PORTA= (0<<PORTA0);



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
adc_init(64);
usart_init();


// initialize the BMP280 sensor
  if(BMP280_begin() == 0)
  {  // connection error or device address wrong!
    lcd_gotoxy(0, 0);   
    putsf("Connection error!");

  }
	

while (1)
      {
    // Read temperature (in hundredths C) and pressure (in Pa)
    // values from BMP280 sensor
    BMP280_readTemperature(&temperature);  // read temperature
    BMP280_readPressure(&pressure);        // read pressure      
    
    i=read_adc(0);                   
    MQ9=(i*100)/1023 ;                     
 
    // print data on the LCD screen
    // 1: print temperature
    // 2: print pressure
    lcd_gotoxy(0, 0);    
    if(temperature < 0)
    {
      putchar('-');
      temperature = abs(temperature);
    }
    else
    
   sprintf(lcd, "%02u.%02u,%04u.%02u,%d", temperature / 100, temperature % 100, pressure / 100, pressure % 100, MQ9);



		puts(lcd);  
        delay_ms(2000);  // wait 2 seconds 
 

 



      }
}
