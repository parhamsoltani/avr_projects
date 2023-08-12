/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 32768Hz crystal on TCNT2
Version : 
Date    : 8/12/2023
Author  : Parham Soltani
Company : 
Comments: 


Chip type               : ATmega32A
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <stdio.h>
#include <alcd.h>
#include <delay.h>
 
unsigned char Buffer[17];
unsigned char second = 20;
unsigned char minute = 20;
unsigned char hour = 20;

void time_write()
{
  sprintf(Buffer,"%02d:%02d:%02d",hour,minute,second);
  lcd_gotoxy(4,0);
  lcd_puts(Buffer);
}

interrupt[5]void Tik_Tik(void)
{
  second++;
  if(second==60)
  {
    second = 0;
    minute++;
    if(minute==60)
    {
      minute = 0;
      hour++;
      if(hour==24) hour = 0;
    }    
  }
    time_write();
}
 
void main(void)
{
  lcd_init(16);
  lcd_clear();
  TIMSK = 0x40;
  TIFR = 0x40;
  #asm ("sei")
  ASSR = 0x08;
  TCNT2 = 0x00;
  TCCR2 = 0x05;
  time_write();
  lcd_gotoxy(3,1);
  lcd_putsf("Approximate Time by PARHAM");
  while(1)
  {
    
  }
  
}
