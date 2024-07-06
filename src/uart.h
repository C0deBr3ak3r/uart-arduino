#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <stdint.h>
#include <util/setbaud.h>

/*
 * [ASYNC | SYNC | SPI]		Whether it's sync, async or in Master SPI Mode
 *
 * ASYNC - SYNC ONLY
 * P[LESS | ODD | EVEN]		Wheter it doesn't have parity, odd parity or even parity
 * [S | D]STOP				Wheter it has single or double stop bits
 * [RISE | FALL]			Clock polarity, only used with sync, it's from the
 *							perspective of TxD0 pin
 * SPI ONLY
 * [M | L]SB				Whether data is transmitted with MSB or LSB first
 * MODEn					SPI Data Mode, refer to the datasheet for more info
 */
enum uart_config : uint8_t {
    UART_ASYNC_PLESS_SSTOP_8C = 0b00000110,
    UART_ASYNC_PLESS_DSTOP_8C = 0b00001110,
    UART_ASYNC_PODD_SSTOP_8C  = 0b00110110,
    UART_ASYNC_PODD_DSTOP_8C  = 0b00111110,
    UART_ASYNC_PEVEN_SSTOP_8C = 0b00100110,
    UART_ASYNC_PEVEN_DSTOP_8C = 0b00101110,

    UART_SYNC_PLESS_SSTOP_8C_RISE = 0b01000110,
    UART_SYNC_PLESS_DSTOP_8C_RISE = 0b01001110,
    UART_SYNC_PODD_SSTOP_8C_RISE  = 0b01110110,
    UART_SYNC_PODD_DSTOP_8C_RISE  = 0b01111110,
    UART_SYNC_PEVEN_SSTOP_8C_RISE = 0b01100110,
    UART_SYNC_PEVEN_DSTOP_8C_RISE = 0b01101110,

    UART_SYNC_PLESS_SSTOP_8C_FALL = 0b01000111,
    UART_SYNC_PLESS_DSTOP_8C_FALL = 0b01001111,
    UART_SYNC_PODD_SSTOP_8C_FALL  = 0b01110111,
    UART_SYNC_PODD_DSTOP_8C_FALL  = 0b01111111,
    UART_SYNC_PEVEN_SSTOP_8C_FALL = 0b01100111,
    UART_SYNC_PEVEN_DSTOP_8C_FALL = 0b01101111,

    UART_SPI_MSB_MODE0 = 0b11000000,
    UART_SPI_MSB_MODE1 = 0b11000001,
    UART_SPI_MSB_MODE2 = 0b11000010,
    UART_SPI_MSB_MODE3 = 0b11000011,
    UART_SPI_LSB_MODE0 = 0b11000000,
    UART_SPI_LSB_MODE1 = 0b11000001,
    UART_SPI_LSB_MODE2 = 0b11000010,
    UART_SPI_LSB_MODE3 = 0b11000011,
};

_Static_assert(sizeof(enum uart_config) == 1, "");

extern void   uart_init(uint16_t baud_rate_reg, enum uart_config config);
extern char   uart_getc(void);
extern void   uart_putc(char data);
extern void   uart_puts(const char* message);
extern void   uart_gets(char* buffer, size_t buf_size);
extern size_t uart_read(void* buffer, size_t buf_size);
extern void   uart_write(const void* buffer, size_t buf_size);

#endif // UART_H
