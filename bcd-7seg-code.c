#include<mega32.h>

#in C you don't have to mention array's length when declaring it
Flash unsigned char bcd_7seg[11]={0x3f,0x06,0x58,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80};
 
Voidmain()
 
{
 
	Unsigned char bcd;
 
	DDRB=0XFF;
 
	While(1)
 
	{
 
		bcd=(PINA&0X0F);
 
		If(bcd<10)PORTB=bcd_7seg[bcd];
 
		ElsePORTB=bcd_7seg[10];
 
	}
 
}

