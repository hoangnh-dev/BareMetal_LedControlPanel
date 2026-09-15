#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "button.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)

int main(void) {
    gpio_init(GPIOB, 2, GPIO_MODE_OUTPUT_PP_10MHZ, GPIO_BANK_B);

    button_init();
    // systick_init(8000000 / 1000);  // 1ms SysTick (assuming 16MHz clock)
    // uint32_t last_toggle = 0;
    // uint8_t led_state = 0;
    while (1) {
        // if ((systick_get_ticks() - last_toggle) >= 500) {
        //     led_state = !led_state;
        //     GPIO_WritePin(GPIOB, 2, led_state);
        //     last_toggle = systick_get_ticks();
        // }
        gpio_write(GPIOB, 2, button_pressed());
    }
}