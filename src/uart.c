#include <avr/io.h>

#include "uart.h"

void uart_init(uint16_t baud_rate_reg, enum uart_config config) {

    // Set baud rate
    UBRR0H = (uint8_t)(baud_rate_reg >> 8);
    UBRR0L = (uint8_t)(baud_rate_reg & 0xFF);

    // Enable TX and RX, Disable interupts
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Apply config
    UCSR0C = config;
}

char uart_getc(void) {
    // Wait until RXB has data
    while ((UCSR0A & (1 << RXC0)) == 0) {
        ;
    }
    return UDR0;
}

void uart_putc(char data) {
    // Wait until transmit buffer is ready to receive new data
    while ((UCSR0A & (1 << UDRE0)) == 0) {
        ;
    }
    UDR0 = data;

    // Wait until there's no new data in transmit buffer
    while ((UCSR0A & (1 << TXC0)) == 0) {
        ;
    }

    return;
}
