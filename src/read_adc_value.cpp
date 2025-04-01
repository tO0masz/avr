// namespace read_adc_value{
// // Read ADC value from pin A0 and print it to the serial monitor
// // AREF connected to 3.3V through 4,7uF capacitor
// // A0 connected to potentiometer

// #include <avr/io.h>
// // include ardino to print to serial monitor
// #include <Arduino.h>

// int read_adc_value(){
    
//     Serial.begin(9600); // Initialize serial communication at 9600 bps

//     uint16_t adc_value = 0; // Variable to store ADC value

//     ADMUX |= (1<<REFS0); // AVCC with external capacitor at AREF pin
//     // No MUXn set, so ADC0 is selected
//     ADCSRA |= (1<<ADEN) | // Enable ADC
//             (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Set prescaler to 128, so clock frequency = 16MHz / 128 = 125kHz
//     while(1){
//         ADCSRA |= (1<<ADSC); // Start conversion
//         while(ADCSRA & (1<<ADSC)); // Wait for conversion to complete
//         adc_value = ADC; // Read ADC value
//         Serial.println(adc_value); // Print ADC value to serial monitor
//     }
// }
// }