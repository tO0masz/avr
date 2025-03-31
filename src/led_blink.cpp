// Toogle PB5 led connected through resistor to GND

#include <avr/io.h>
#include <util/delay.h>

int led_blink(){
  DDRB = 0xFF; // Set PORTB as output
  PORTB = 0x00; // Initialize PORTB to 0
  while(1){
    PORTB |= (1<<PB5); // Set PB5 high
    _delay_ms(500); // Wait for 500 milliseconds
    PORTB &= ~(1<<PB5); // Set PB5 low
    _delay_ms(500); // Wait for 500 milliseconds
  }
}