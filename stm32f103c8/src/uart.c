#include "uart.h"
#include "gpio.h"

#define uart1_tx_pin 9
#define uart1_rx_pin 10
#define APB2_FREQUENCY 8000000U    //clock

/* RCC_APB2ENR bit definitions */
#define RCC_APB2ENR_USART1EN_Pos   14U
#define RCC_APB2ENR_USART1EN_Msk   (1U << RCC_APB2ENR_USART1EN_Pos)

/* USARTx_CR1 bit definitions */
#define USART_CR1_UE_Pos           13U   // USART enable
#define USART_CR1_UE_Msk           (1U << USART_CR1_UE_Pos)
#define USART_CR1_TE_Pos           3U    // Transmitter enable
#define USART_CR1_TE_Msk           (1U << USART_CR1_TE_Pos)
#define USART_CR1_RE_Pos           2U    // Receiver enable
#define USART_CR1_RE_Msk           (1U << USART_CR1_RE_Pos)

/* USARTx_SR bit definitions */
#define USART_SR_TXE_Pos           7U    // Transmit data register empty
#define USART_SR_TXE_Msk           (1U << USART_SR_TXE_Pos)
#define USART_SR_RXNE_Pos          5U    // Read data register not empty
#define USART_SR_RXNE_Msk          (1U << USART_SR_RXNE_Pos)

void uart_init(uart_t *uart, unsigned long baud){
    uint32_t pclk = 0;
    if (uart == USART1) {
        RCC->RCC_APB2ENR |= RCC_APB2ENR_USART1EN_Msk; // Enable USART1 clock
        gpio_init(GPIOA, uart1_tx_pin, GPIO_MODE_AF_PP_50MHZ, GPIO_BANK_A); 
        gpio_init(GPIOA, uart1_rx_pin, GPIO_MODE_INPUT_FLOATING, GPIO_BANK_A);
        pclk = APB2_FREQUENCY;
    }

    // Clear CR1 to disable USART and reset settings
    uart->CR1 = 0;

    uint32_t div = (pclk + (baud / 2)) / baud;
    uart->BRR = div;

    uart->CR1 |= USART_CR1_UE_Msk | USART_CR1_TE_Msk | USART_CR1_RE_Msk;
}

uint8_t uart_read_byte(uart_t *uart) {
    return (uint8_t)(uart->DR);
}

void uart_write_char(uart_t *uart, char ch) {
    while (!(uart->SR & USART_SR_TXE_Msk)) (void)0; // Wait until TXE bit is set, indicating data register is empty
    uart->DR = (uint32_t)ch;
}

void uart_write_buf(uart_t *uart,const char *buf) {
    size_t len = 0;
    while (buf[len] != '\0') {
        uart_write_char(uart, buf[len]);
        len++;
    }
}

void uart_flush_rx(uart_t *uart) {
    while (uart->SR & USART_SR_RXNE_Msk) { 
        (void)uart->DR;
    }
}

char uart_read_char(uart_t *uart){
    uart_flush_rx(uart);
    while (!(uart->SR & USART_SR_RXNE_Msk)) (void)0; // Wait until RXNE bit is set
    return (char)uart->DR;
}