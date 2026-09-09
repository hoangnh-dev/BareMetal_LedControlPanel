#include "rcc.h"
#include "gpio.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)


static void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    RCC->RCC_APB2ENR |= (1 << 3);          // open clock for GPIOB (bit 3 = IOPBEN)
    GPIO_Init(GPIOB, 2, GPIO_MODE_OUTPUT_PP_10MHZ);

    while (1) {
        GPIO_WritePin(GPIOB, 2, 1); // LED on 
        delay(500000);
        GPIO_WritePin(GPIOB, 2, 0); // LED off    
        delay(500000);
    }
}