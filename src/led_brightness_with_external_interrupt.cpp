// // Read ADC value from pin A0 and print it to the serial monitor
// // AREF connected to 3.3V through 4,7uF capacitor
// // A0 connected to potentiometer
// // Controll PD6 led output connected through resistor to GND
// // This code will controll light output for the OC0A (PD6) led with readed ADC value and PWM
// // Activate led when External interrupt comes to pin PD4 (PCINT20) from Sharp GP2Y0D810Z0F distance sensor
// // This code updates the led brightness when the interrupt is triggered on PD4 (PCINT20)

// #include <avr/io.h>
// // include ardino to print to serial monitor
// #include <Arduino.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>

// #define F_CPU 16000000UL // Define CPU frequency 

// volatile uint16_t adc_value = 0; // Variable to store ADC value
// volatile bool led_on = false; // Variable to store LED state

// ISR(PCINT2_vect){
//     if(led_on){
//         led_on = false;
//         OCR0A = adc_value / 4; // Set LED brightness based on ADC value (0-255)
//     }
//     else{
//         led_on = true;
//     }
// }

// void setupADC(){
//     ADMUX |= (1<<REFS0); // AVCC with external capacitor at AREF pin
//     // No MUXn set, so ADC0 is selected
//     ADCSRA |= (1<<ADEN) | // Enable ADC
//             (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Set prescaler to 128, so clock frequency = 16MHz / 128 = 125kHz
// }

// void setupLed(){
//     // Setup Timer0 for PWM
//     TCCR0A |= (1<<WGM00) | (1<<WGM01) | // Fast PWM mode
//                 (1<<COM0A1); // Clear OC0A on Compare Match when up-counting. Set OC0A on Compare Match when down-counting
//     TCCR0B |= (1<<CS02) | (1<<CS00); // Set prescaler to 1024
//     OCR0A = 0; // Set initial compare value to 0
//     DDRD |= (1<<PD6); // Set OC0A (PD6) as output
// }

// void setupInterrupt(){
//     cli(); // Disable global interrupts
//     DDRD &= ~(1<<PD4); // Set PD4 as input for interrupt
//     PCICR |= (1<<PCIE2); // Enable pin change interrupt for PCINT[23:16]
//     PCMSK2 |= (1<<PCINT20); // Enable pin change interrupt for PD4 (PCINT20)
//     sei(); // Enable global interrupts
// }

// int main(){
    
//     Serial.begin(9600); // Initialize serial communication at 9600 bps

//     setupADC(); // Setup ADC

//     setupLed(); // Setup LED

//     setupInterrupt(); // Setup interrupt


//     while(1){
//         ADCSRA |= (1<<ADSC); // Start conversion
//         while(ADCSRA & (1<<ADSC)); // Wait for conversion to complete
//         adc_value = ADC; // Read ADC value
//         Serial.println(adc_value); // Print ADC value to serial monitor
//     }
// }