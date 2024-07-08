#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <stdint.h>
#include <util/setbaud.h>

/*
 * [ASYNC | SYNC | SPI]		Whether it's sync, async or in Master SPI Mode
 *
 * ASYNC - SYNC ONLY
 * It's ALWAYS 8 bits/character
 * P[LESS | ODD | EVEN]		Wheter it doesn't have parity, odd parity or even parity
 * [S | D]STOP				Wheter it has single or double stop bits
 * [RISE | FALL]			Clock polarity, only used with sync, it's from the
 *							perspective of TxD0 pin
 * SPI ONLY
 * [M | L]SB				Whether data is transmitted with MSB or LSB first
 * MODEn					SPI Data Mode, refer to the datasheet for more info
 */
#define UART_ASYNC_PLESS_SSTOP     0x06 // 0b00000110
#define UART_ASYNC_PLESS_DSTOP     0x0e // 0b00001110
#define UART_ASYNC_PODD_SSTOP      0x36 // 0b00110110
#define UART_ASYNC_PODD_DSTOP      0x3e // 0b00111110
#define UART_ASYNC_PEVEN_SSTOP     0x26 // 0b00100110
#define UART_ASYNC_PEVEN_DSTOP     0x2e // 0b00101110
#define UART_SYNC_PLESS_SSTOP_RISE 0x46 // 0b01000110
#define UART_SYNC_PLESS_DSTOP_RISE 0x4e // 0b01001110
#define UART_SYNC_PODD_SSTOP_RISE  0x76 // 0b01110110
#define UART_SYNC_PODD_DSTOP_RISE  0x7e // 0b01111110
#define UART_SYNC_PEVEN_SSTOP_RISE 0x66 // 0b01100110
#define UART_SYNC_PEVEN_DSTOP_RISE 0x6e // 0b01101110
#define UART_SYNC_PLESS_SSTOP_FALL 0x47 // 0b01000111
#define UART_SYNC_PLESS_DSTOP_FALL 0x4f // 0b01001111
#define UART_SYNC_PODD_SSTOP_FALL  Ox77 // 0b01110111
#define UART_SYNC_PODD_DSTOP_FALL  Ox7f // 0b01111111
#define UART_SYNC_PEVEN_SSTOP_FALL Ox67 // 0b01100111
#define UART_SYNC_PEVEN_DSTOP_FALL Ox6f // 0b01101111
#define UART_SPI_MSB_MODE0         OxC0 // 0b11000000
#define UART_SPI_MSB_MODE1         OxC1 // 0b11000001
#define UART_SPI_MSB_MODE2         OxC2 // 0b11000010
#define UART_SPI_MSB_MODE3         OxC3 // 0b11000011
#define UART_SPI_LSB_MODE0         OxC0 // 0b11000000
#define UART_SPI_LSB_MODE1         OxC1 // 0b11000001
#define UART_SPI_LSB_MODE2         OxC2 // 0b11000010
#define UART_SPI_LSB_MODE3         OxC3 // 0b11000011

extern void uart_init(uint16_t baud_rate_reg, uint8_t config);
extern char uart_getc(void);
extern void uart_putc(char data);
extern void uart_puts(const char* message);
extern void uart_gets(char* buffer, size_t buf_size);
extern void uart_read(void* buffer, size_t buf_size);
extern void uart_write(const void* buffer, size_t buf_size);

#endif // UART_H
