#include <mega32a.h>
#include <delay.h>

#define VibrationSensor_PIN PIND2 // Vibration Sensor Input Pin (PD2)
#define LED_PIN             PINB0 // LED Output Pin (PB0)

void vibration_sensor_demo() {
    // Set Vibration Sensor pin as input and LED pin as output
    DDRD &= ~(1 << VibrationSensor_PIN); // Set PD2 as input for vibration sensor
    PORTD &= ~(1 << VibrationSensor_PIN); // Disable internal pull-up for PD2
    DDRB |= (1 << LED_PIN); // Set PB0 as output for LED
    PORTB &= ~(1 << LED_PIN); // Turn LED Off

    while (1) {
        unsigned char vibrationValue = (PIND & (1 << VibrationSensor_PIN)); // Read Vibration Sensor value (PD2)
        if (vibrationValue) {
            PORTB |= (1 << LED_PIN); // Turn LED On (PB0)
        } else {
            PORTB &= ~(1 << LED_PIN); // Turn LED Off (PB0)
        }
    }
}


//With this code, the AVR will continuously read the vibration sensor value connected to PD2 (VibrationSensor_PIN) and control the LED connected to PB0 (LED_PIN) based on //the sensor's input. You can call the vibration_sensor_demo() function once in your program to activate the vibration sensor and LED control functionality. Make sure to //connect the vibration sensor output pin to PD2 on the AVR microcontroller and the LED to PB0 for this code to work correctly.