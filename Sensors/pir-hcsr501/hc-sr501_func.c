#include <mega32a.h>
#include <delay.h>
#include <alcd.h>

// Function prototypes
void motion_detection();

void main(void)
{
    // Initialization code (same as before) goes here

    lcd_init(16);

    while (1)
    {
        motion_detection();
        delay_ms(300);
    }
}

// Function for motion detection using the PIR sensor and displaying the result on the LCD
void motion_detection()
{
    int PIR;
    PIR = PINA.0;
    PORTD.0 = PIR;
    lcd_clear();
    lcd_gotoxy(0, 0);
    if (PIR == 1)
    {
        lcd_putsf("Motion detected");
    }
    else
    {
        lcd_putsf("motionless");
    }
}
