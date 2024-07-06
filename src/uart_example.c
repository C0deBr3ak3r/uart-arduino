#include <util/delay.h>

#include "uart.h"

int main(void) {
    uart_init(F_CPU / 16 / BAUD - 1, UART_ASYNC_PLESS_DSTOP_8C);
    while (1) {
        _delay_ms(1 * 1000);

        uart_putc('H');
        uart_putc('e');
        uart_putc('l');
        uart_putc('l');
        uart_putc('o');
        uart_putc(' ');
        uart_putc('w');
        uart_putc('o');
        uart_putc('r');
        uart_putc('l');
        uart_putc('d');
        uart_putc('\n');
    }
    return 0;
}
