#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "button.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)

int main(void) {
    RCC->RCC_APB2ENR |= (1 << 3);          // open clock for GPIOB (bit 3 = IOPBEN)
    GPIO_Init(GPIOB, 2, GPIO_MODE_OUTPUT_PP_10MHZ);
    RCC->RCC_APB2ENR |= (1 << 2);          // open clock for GPIOA (bit 2 = IOPAEN)
    button_init(GPIOA,0);
    // systick_init(8000000 / 1000);  // 1ms SysTick (assuming 16MHz clock)
    // uint32_t last_toggle = 0;
    // uint8_t led_state = 0;
    while (1) {
        // if ((systick_get_ticks() - last_toggle) >= 500) {
        //     led_state = !led_state;
        //     GPIO_WritePin(GPIOB, 2, led_state);
        //     last_toggle = systick_get_ticks();
        // }
        GPIO_WritePin(GPIOB, 2, button_read(GPIOA, 0));
    }
}