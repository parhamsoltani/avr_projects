////////// WWW.EMIC.IR //////////
#include <mega16a.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>    // sprintf ���� ������� �� ���� stdio �������� �������� //
//����� �� ���� adc �� ���� ��� ����� �� �������� adc �� �� 7 �� 16 ������� ����� ��//
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
float  A;  //�� �� 20 �� 22 ������ ����� ���� ������� �� ������ ����� ��� ���//
int  L;    
unsigned char lcd[16];
//���� ����� ��� ��� A �� ��� ����//
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
//���� ���� ����� �� �� �� �� ���ǘ��� ����� ��� ��� D �� ��� ����//
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);
//�� �� ���� �� ������� �� �� ���� �������� ����� �� ���� adc �� �� 34 �� 36 ��������� ����� ��//
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
      A=read_adc(0);                 //���� ��� A ������ ���� ��� 0 �� 1023 �� ����� ����� ���ǎ ����� ��� ��� 0 �� ����//
      L=(A*100)/1023;                //����� ����� ��� ������ ��� ��� 0 �� 1023 �� �� ���� � 0 �� 100 ����� �� ���//  
      lcd_gotoxy(0,0);               //���� �� ���� 0 � ��� 0 �� �� �� �� ���ǘ���// 
      lcd_putsf("amount of light");  //��� �� �� �� ���ǘ��� amount of light ����� �����//
      lcd_gotoxy(6,1);               //���� �� ���� 6 � ��� 0 �� �� �� �� ���ǘ���// 
      sprintf(lcd,"%d",L);           //���� ����� ��� �� �� �� ���ǘ��� lcd �� ���� �� �� ���ǘ�� � ����� �� �� ����� L ����� ������ ����� �� �����//
      lcd_puts(lcd);                 //����� ���� ����� lcd ����� ����� ��� ���� (�� ����) �� �� ���� ���ǘ�� �� �����//                                         
      lcd_putsf("%");                // % ����� ���ǘ�� //    
      delay_ms(500);                 //����� 500 ���� ����� �����// 
      lcd_clear();                   //�ǘ ���� �� �� �� ���ǘ���//
      }
}