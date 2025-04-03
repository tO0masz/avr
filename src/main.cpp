// Controll BH1750 sensor via I2C and print the value to serial monitor
// Set BH1750 addres pin to GND co the address is 0100011 (0x23)  

#include <avr/io.h>
// include ardino to print to serial monitor
#include <Arduino.h>
#include <util/delay.h>

#define F_CPU 16000000UL // Define CPU frequency 
#define SCL_CLOCK 400000L // Define SCL clock frequency 400kHz
#define BH1750_ADDRESS 0x23 // Define BH1750 address

void i2c_init(){
    TWSR = 0x00; // Set TWI prescaler to 0
    // SCLf = F_CPU / (16 + (2 * (SCL_CLOCK) * PRESCALER)) Set TWI bit rate register
    // TWBR = ((F_CPU / SCL_CLOCK) - 16) / (2 * PRESCALER); // Set TWI bit rate register
    // TWBR = ((16000000 / 400000) - 16) / 2 = 12
    TWBR = 0xC; // Set TWI bit rate register
}

void i2c_start(){
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send start condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
}

void i2c_stop(){
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); // Send stop condition
}

uint8_t i2c_write(uint8_t data){
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN); // Start transmission
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
    return (TWSR & 0xF8); // Return status register
}

uint8_t i2c_read_ack(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Read with ACK
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

uint8_t i2c_read_nack(void) {
    TWCR = (1 << TWINT) | (1 << TWEN); // Read without ACK
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

int main(){
    
    Serial.begin(9600); // Initialize serial communication at 9600 bps

    i2c_init(); // Initialize I2C
    volatile uint8_t data1;
    volatile uint8_t data2;
    volatile uint16_t lux;

    while(1){
        i2c_start(); // Send start condition
        i2c_write(BH1750_ADDRESS << 1); // Send BH1750 address with write bit
        // Send command to start measurement in high resolution mode
        i2c_write(0x10); // Start measurement in high resolution mode (1lx resolution)
        i2c_stop(); // Send stop condition
        _delay_ms(180); // Wait for measurement to complete (Measurement Time is typically 120ms)

        i2c_start(); // Send start condition
        i2c_write(BH1750_ADDRESS << 1 | 1); // Send BH1750 address with read bit
        data1 = i2c_read_ack(); // Read first byte (high byte)
        data2 = i2c_read_nack(); // Read second byte (low byte)
        i2c_stop(); // Send stop condition

        lux = (data1 << 8) | data2; // Combine high and low byte to get lux value
        Serial.println(lux); // Print lux value to serial monitor
    }
}