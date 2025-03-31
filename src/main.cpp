#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(){
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