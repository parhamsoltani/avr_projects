#include <mega32a.h>
#include <delay.h>

#define Sensor_PIN PIND2  // RCWL-0516 Input Pin (PD2)
#define LED_PIN    PINB0  // LED Output Pin (PB0)

void rcwl0516_latch_demo() {
    // Set Sensor pin as input and LED pin as output
    DDRD &= ~(1 << Sensor_PIN); // Set PD2 as input
    PORTD &= ~(1 << Sensor_PIN); // Disable internal pull-up for PD2
    DDRB |= (1 << LED_PIN); // Set PB0 as output
    PORTB &= ~(1 << LED_PIN); // Turn LED Off
    
    while (1) {
        unsigned char SensValue = (PIND & (1 << Sensor_PIN)); // Read Sensor value (PD2)
        if (SensValue) {
            PORTB |= (1 << LED_PIN); // Turn LED On (PB0)
        } else {
            PORTB &= ~(1 << LED_PIN); // Turn LED Off (PB0)
        }
    }
}


//In this code, the rcwl0516_latch_demo() function is responsible for reading the sensor value from PD2 and controlling the LED connected to PB0 based on that value.
//The setup() function sets up the pins for the sensor and LED, while the loop() function calls the rcwl0516_latch_demo() function in a continuous loop.
//Please make sure to connect the sensor's output pin to PD2 (Sensor_PIN) on the AVR microcontroller and the LED to PB0 (LED_PIN) for this code to work correctly.