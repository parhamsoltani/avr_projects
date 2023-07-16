#include <mega32.h>

void main ()
{
   DDRB= (1<<DDB3);
   PORTB=(1<<PORTB0);
   OCR0=100;
   TCCR0=(1<<COM00)|(1<<CS02)|(1<<CSO1);
  while(1);
}
