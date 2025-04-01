// Read ADC value from pin A0 and print it to the serial monitor
// AREF connected to 3.3V through 4,7uF capacitor
// A0 connected to potentiometer
// Toogle PB5 led connected through resistor to GND
// This code will toggle the PB5 pin with time set with readed ADC value

#include <avr/io.h>
// include ardino to print to serial monitor
#include <Arduino.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define CPU frequency 

volatile uint16_t adc_value = 0; // Variable to store ADC value

ISR(TIMER1_COMPA_vect) {
  OCR1A = adc_value; // Set compare value for Timer1
  PORTB ^= (1 << PB5); // Toggle PB5
}

void setupADC(){
    ADMUX |= (1<<REFS0); // AVCC with external capacitor at AREF pin
    // No MUXn set, so ADC0 is selected
    ADCSRA |= (1<<ADEN) | // Enable ADC
            (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Set prescaler to 128, so clock frequency = 16MHz / 128 = 125kHz
}

void setupLed(){
    cli(); // Disable global interrupts
    DDRB = 0xFF; // Set PORTB as output
    PORTB = 0x00; // Initialize PORTB to 0

    // Set up Timer1
    TCCR1B |= (1<<WGM12); // Set CTC mode
    TCCR1B |= (1<<CS10) | (1<<CS12); // Set prescaler to 1024
    OCR1A = 0; // Set compare value
    TIMSK1 |= (1<<OCIE1A); // Enable Timer1 compare A interrupt
    sei(); // Enable global interrupts
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
    }
}