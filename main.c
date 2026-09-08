#include "rcc.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)


static void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    RCC->RCC_APB2ENR |= (1 << 3);         // open clock for GPIOB (bit 3 = IOPBEN)

    GPIOB_CRL &= ~(0xFU << (2 * 4));   // reset PB2 
    GPIOB_CRL |=  (0x2U << (2 * 4));    // set PB2 = output 10MHz (0001)

    while (1) {
        GPIOB_BSRR = (1 << 2);        // LED on
        delay(500000);
        GPIOB_BSRR = (1 << (2 + 16));        // LED off
        delay(500000);
    }
}