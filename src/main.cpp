// Read ADC value from pin A0 and print it to the serial monitor
// AREF connected to 3.3V through 4,7uF capacitor
// A0 connected to potentiometer
// Controll PD6 led output connected through resistor to GND
// This code will controll light output for the OC0A (PD6) led with readed ADC value and PWM

#include <avr/io.h>
// include ardino to print to serial monitor
#include <Arduino.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define CPU frequency 

volatile uint16_t adc_value = 0; // Variable to store ADC value

void setupADC(){
    ADMUX |= (1<<REFS0); // AVCC with external capacitor at AREF pin
    // No MUXn set, so ADC0 is selected
    ADCSRA |= (1<<ADEN) | // Enable ADC
            (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Set prescaler to 128, so clock frequency = 16MHz / 128 = 125kHz
}

void setupLed(){
    // Setup Timer0 for PWM
    TCCR0A |= (1<<WGM00) | (1<<WGM01) | // Fast PWM mode
                (1<<COM0A1); // Clear OC0A on Compare Match when up-counting. Set OC0A on Compare Match when down-counting
    TCCR0B |= (1<<CS02) | (1<<CS00); // Set prescaler to 1024
    OCR0A = 0; // Set initial compare value to 0
    DDRD |= (1<<PD6); // Set OC0A (PD6) as output
}

int main(){
    
    Serial.begin(9600); // Initialize serial communication at 9600 bps

    setupADC(); // Setup ADC

    setupLed(); // Setup LED


    while(1){
        ADCSRA |= (1<<ADSC); // Start conversion
        while(ADCSRA & (1<<ADSC)); // Wait for conversion to complete
        adc_value = ADC; // Read ADC value
        Serial.println(adc_value); // Print ADC value to serial monitor
        _delay_ms(100); // Delay for 100ms to avoid excessive ADC sampling and allow time for serial communication
        OCR0A = adc_value / 4; // Set PWM value (ADC value is 10-bit, so divide by 4 to fit in 8-bit OCR0A)
    }
}