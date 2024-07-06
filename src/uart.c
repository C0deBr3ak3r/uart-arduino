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

// TODO: Document defines `UART_TRAILING_NEW_LINE`, `UART_CRLF`
void uart_puts(const char* message) {
    for (size_t i = 0; message[i] != '\0'; i++) {
        // Wait until transmit buffer is ready to receive new data
        while ((UCSR0A & (1 << UDRE0)) == 0) {
            ;
        }
#ifdef UART_CRLF
        if (message[i] == '\n' && message[i - 1] != '\r') {
            UDR0 = '\r';
        }
        while ((UCSR0A & (1 << UDRE0)) == 0) {
            ;
        }
#endif

        UDR0 = message[i];
    }
#ifdef UART_TRAILING_NEWLINE
#ifdef UART_CRLF
    while ((UCSR0A & (1 << UDRE0)) == 0) {
        ;
    }
    UDR0 = '\r';
#endif
    while ((UCSR0A & (1 << UDRE0)) == 0) {
        ;
    }
    UDR0 = '\n';
#endif
    // Wait until there's no new data in transmit buffer
    while ((UCSR0A & (1 << TXC0)) == 0) {
        ;
    }

    return;
}

// Stops when buffer is full, a NUL byte, a carriage return (\r) or a new line (\n) is written,
// preserving them
void uart_gets(char* buffer, size_t buf_size) {
    size_t chars_readed = 0;

    while (chars_readed < (buf_size - 1)) {
        // Wait until RXB has data
        while ((UCSR0A & (1 << RXC0)) == 0) {
            ;
        }
        buffer[chars_readed++] = UDR0;
        if (buffer[chars_readed - 1] == '\r' || buffer[chars_readed - 1] == '\0' ||
            buffer[chars_readed - 1] == '\n') {
            break;
        }
    }
    buffer[chars_readed] = '\0';

    return;
}

void uart_read(void* buffer, size_t buf_size) {
    uint8_t* buf_cpy = (uint8_t*)buffer;

    for (size_t i = 0; i < (buf_size); i++) {
        // Wait until RXB has data
        while ((UCSR0A & (1 << RXC0)) == 0) {
            ;
        }
        buf_cpy[i] = UDR0;
    }
    return;
}

void uart_write(const void* buffer, size_t buf_size) {
    uint8_t* buf_cpy = (uint8_t*)buffer;
    for (size_t i = 0; i < buf_size; i++) {
        // Wait until transmit buffer is ready to receive new data
        while ((UCSR0A & (1 << UDRE0)) == 0) {
            ;
        }

        UDR0 = buf_cpy[i];
    }
}
