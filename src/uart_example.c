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

        uart_puts("It was lots of putc's");
        uart_puts("Input 7 characters:");
        char buf[8];
        uart_gets(buf, sizeof(char) * 8);
        uart_puts("This was your input: ");
        uart_puts(buf);
    }
    return 0;
}
