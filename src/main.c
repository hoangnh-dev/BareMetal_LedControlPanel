#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "button.h"
#include "led.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)

int main(void) {
    systick_init(8000000 / 1000);
    led_init();
    button_init();
    while (1) {
        if (button_pressed() == 1){
            led_next_mode();
        }
        led_update();
    }
}