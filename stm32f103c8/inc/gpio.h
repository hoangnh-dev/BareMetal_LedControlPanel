#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include "rcc.h"
typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} gpio_t;

typedef enum {
    // ---------- INPUT modes (MODE=00) ---------------
    GPIO_MODE_INPUT_ANALOG      = 0x0,  // 00 00
    GPIO_MODE_INPUT_FLOATING    = 0x4,  // 01 00
    GPIO_MODE_INPUT_PUPD        = 0x8,  // 10 00

    // ----- OUTPUT modes, speed 10MHz (MODE=01) -----
    GPIO_MODE_OUTPUT_PP_10MHZ   = 0x1,  // 00 01
    GPIO_MODE_OUTPUT_OD_10MHZ   = 0x5,  // 01 01
    GPIO_MODE_AF_PP_10MHZ       = 0x9,  // 10 01
    GPIO_MODE_AF_OD_10MHZ       = 0xD,  // 11 01

    // ----- OUTPUT modes, speed 2MHz (MODE=10) -----
    GPIO_MODE_OUTPUT_PP_2MHZ    = 0x2,  // 00 10
    GPIO_MODE_OUTPUT_OD_2MHZ    = 0x6,  // 01 10
    GPIO_MODE_AF_PP_2MHZ        = 0xA,  // 10 10
    GPIO_MODE_AF_OD_2MHZ        = 0xE,  // 11 10

    // ----- OUTPUT modes, speed 50MHz (MODE=11) -----
    GPIO_MODE_OUTPUT_PP_50MHZ   = 0x3,  // 00 11
    GPIO_MODE_OUTPUT_OD_50MHZ   = 0x7,  // 01 11
    GPIO_MODE_AF_PP_50MHZ       = 0xB,  // 10 11
    GPIO_MODE_AF_OD_50MHZ       = 0xF,  // 11 11
} gpio_mode_t;

#define GPIOA_BASE  0x40010800UL
#define GPIOB_BASE  0x40010C00UL
#define GPIOC_BASE  0x40011000UL
#define GPIOD_BASE  0x40011400UL

#define GPIOA  ((gpio_t *)GPIOA_BASE)
#define GPIOB  ((gpio_t *)GPIOB_BASE)
#define GPIOC  ((gpio_t *)GPIOC_BASE)
#define GPIOD  ((gpio_t *)GPIOD_BASE)

typedef enum {
    GPIO_BANK_A = 2,
    GPIO_BANK_B,
    GPIO_BANK_C,
    GPIO_BANK_D,
} gpio_bank_t;


void gpio_init(gpio_t *port, uint8_t pin, gpio_mode_t  mode, gpio_bank_t bank);
void gpio_write(gpio_t *port, uint8_t pin, uint8_t value);
uint8_t gpio_read(gpio_t *port, uint8_t pin);

#endif