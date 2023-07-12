#include<mega32.h>

Void main()
{
  //DDRB=0X01;
  DDRB=(1<<DDB0);
  //PORTB=0X01;
  PORTB=(1<<PORTB0);
  While(1);
}
