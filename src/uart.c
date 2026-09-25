#include "uart.h"
#include "gpio.h"

#define uart1_tx_pin 9
#define uart1_rx_pin 10
#define APB2_FREQUENCY 8000000U

void uart_init(uart_t *uart, unsigned long baud){
    uint32_t pclk = 0;
    if (uart == USART1) {
        RCC->RCC_APB2ENR |= (1U << 14); // Enable USART1 clock
        gpio_init(GPIOA, uart1_tx_pin, GPIO_MODE_AF_PP_50MHZ, GPIO_BANK_A); 
        gpio_init(GPIOA, uart1_rx_pin, GPIO_MODE_INPUT_FLOATING, GPIO_BANK_A);
        pclk = APB2_FREQUENCY;
    }

    // Clear CR1 to disable USART and reset settings
    uart->CR1 = 0;

    uint32_t div = (pclk + (baud / 2)) / baud;
    uart->BRR = div;

    uart->CR1 |= (1U << 13) | (1U << 3) | (1U << 2);
}

uint8_t uart_read_byte(uart_t *uart) {
    return (uint8_t)(uart->DR);
}

void uart_write_char(uart_t *uart, char ch) {
    while (!(uart->SR & (1U << 7))) (void)0; // Wait until TXE bit is set, indicating data register is empty
    uart->DR = (uint32_t)ch;
}

void uart_write_buf(uart_t *uart,const char *buf, size_t len) {
    while (len-- > 0)   uart_write_char(uart, *(uint8_t *)buf++);
}

char uart_read_char(uart_t *uart){
    while (!(uart->SR & (1U << 5))) (void)0; // Wait until RXNE bit is set
    return (char)uart->DR;
}