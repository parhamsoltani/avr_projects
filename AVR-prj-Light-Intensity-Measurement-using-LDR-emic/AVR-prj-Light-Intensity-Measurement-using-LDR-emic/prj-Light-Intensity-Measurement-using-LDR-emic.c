////////// WWW.EMIC.IR //////////
#include <mega16a.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>    // sprintf ÈÑÇí ÇÓÊİÇÏå ÇÒ ÊÇÈÚ stdio İÑÇÎæÇäí ˜ÊÇÈÎÇäå //
//ÇíÌÇÏ ãí ÔæäÏ adc ˜å ÊæÓØ ÎæÏ ˜Ïæíä ÈÇ İÚÇáÓÇÒí adc ÇÒ ÎØ 7 ÊÇ 16 ÏÓÊæÑÇÊ ãÑÈæØ Èå//
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
float  A;  //ÇÒ ÎØ 20 ÊÇ 22 ÊÚÏÇÏí ãÊÛíÑ ÈÑÇí ÇÓÊİÇÏå ÏÑ ÈÑäÇãå ÊÚÑíİ ÔÏå ÇÓÊ//
int  L;    
unsigned char lcd[16];
//ãí˜Ñæ æÑæÏí ÔÏå ÇÓÊ A ÏÑ ÒíÑ æÑÊ//
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
//ãí˜Ñæ ÈÑÇí ÇÊÕÇá Èå Çá Óí Ïí ˜ÇÑÇ˜ÊÑí ÎÑæÌí ÔÏå ÇÓÊ D ÏÑ ÒíÑ æÑÊ//
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
//˜å ÈÇ ÊæÌå Èå ÊäÙíãÇÊ ãÇ ÏÑ ãÍíØ ˜ÏæíÒÇÑÏ ÇíÌÇÏ ãí ÔæäÏ adc ÇÒ ÎØ 34 ÊÇ 36 ÑÌíÓÊÑåÇí ãÑÈæØ Èå//
// ADC initialization
// ADC Clock frequency: 500/000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

lcd_init(16);

lcd_clear();
lcd_gotoxy(2,0);
lcd_putsf("WWW.EMIC.IR");
delay_ms(2000);

while (1)
      {
      A=read_adc(0);                 //ãí˜Ñæ ÇÓÊ A ÎæÇäÏä ÚÏÏí Èíä 0 ÊÇ 1023 ˜å ÈíÇäÑ ãŞÏÇÑ æáÊÇ ÇäÇáæ Ñæí íä 0 ÇÒ æÑÊ//
      L=(A*100)/1023;                //ÏÓÊæÑ ÑæÈÑæ ÚÏÏ ÎæÇäÏå ÔÏå Èíä 0 ÊÇ 1023 ÑÇ ÏÑ ÈÇÒå í 0 ÊÇ 100 ÊÈÏíá ãí ˜äÏ//  
      lcd_gotoxy(0,0);               //ÑİÊä Èå ÓÊæä 0 æ ÓØÑ 0 ÇÒ Çá Óí Ïí ˜ÇÑÇ˜ÊÑí// 
      lcd_putsf("amount of light");  //Ñæí Çá Óí Ïí ˜ÇÑÇ˜ÊÑí amount of light äãÇíÔ ÚÈÇÑÊ//
      lcd_gotoxy(6,1);               //ÑİÊä Èå ÓÊæä 6 æ ÓØÑ 0 ÇÒ Çá Óí Ïí ˜ÇÑÇ˜ÊÑí// 
      sprintf(lcd,"%d",L);           //ÈÑÇí äãÇíÔ Ñæí Çá Óí Ïí ˜ÇÑÇ˜ÊÑí lcd Èå ÑÔÊå Çí ÇÒ ˜ÇÑÇ˜ÊÑ æ ĞÎíÑå Çä ÏÑ ãÊÛíÑ L ÊÈÏíá ãŞÇÏíÑ ãæÌæÏ ÏÑ ãÊÛíÑ//
      lcd_puts(lcd);                 //ĞÎíÑå ˜ÑÏå ÈæÏíã lcd äãÇíÔ ãŞÏÇÑ äæÑ ãÍíØ (Èå ÏÑÕÏ) ˜å Èå ÕæÑÊ ˜ÇÑÇ˜ÊÑ ÏÑ ãÊÛíÑ//                                         
      lcd_putsf("%");                // % äæÔÊä ˜ÇÑÇ˜ÊÑ //    
      delay_ms(500);                 //ÇíÌÇÏ 500 ãíáí ËÇäíå ÊÇÎíÑ// 
      lcd_clear();                   //Ç˜ ˜ÑÏä Çá Óí Ïí ˜ÇÑÇ˜ÊÑí//
      }
}