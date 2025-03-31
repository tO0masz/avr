// Toogle PB5 led connected through resistor to GND using internal interrupts
// This code will toggle the PB5 pin every 500ms using an interrupt.

// Formula for the counter operating frequency: ftimer = fCPU / prescaler
// Formula for accurate time: t = (OCR1A + 1) / ftimer

// ftimer = 16MHz / 1024 = 15625Hz
// OCR1A = (0.5s * 15625Hz) - 1 = 7811,5 => 7812

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL // Define CPU frequency 

// Timer1 interrupt service routine
// This function is called when Timer1 reaches the value in OCR1A
ISR(TIMER1_COMPA_vect) {
    PORTB ^= (1 << PB5); // Toggle PB5
}

int led_blink_interrupt(){
    cli(); // Disable global interrupts
    DDRB = 0xFF; // Set PORTB as output
    PORTB = 0x00; // Initialize PORTB to 0

    // Set up Timer1
    TCCR1B |= (1<<WGM12); // Set CTC mode
    TCCR1B |= (1<<CS10) | (1<<CS12); // Set prescaler to 1024
    OCR1A = 7812; // Set compare value for 500ms delay
    TIMSK1 |= (1<<OCIE1A); // Enable Timer1 compare A interrupt
    sei(); // Enable global interrupts

    while(1){

    }
}