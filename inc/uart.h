#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>

typedef struct{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} uart_t;

#define USART1 ((uart_t *)0x40013800)

void uart_init(uart_t *uart, unsigned long baud);
int uart_read_ready(uart_t *uart);
int uart_write_ready(uart_t *uart);
void uart_write_char(uart_t *uart, char c);
void uart_write_buf(uart_t *uart,const char *buf, size_t len);
char uart_read_char(uart_t *uart);

#endif