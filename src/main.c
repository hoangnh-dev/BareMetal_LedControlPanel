#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "button.h"
#include "led.h"
#include "exti.h"
#include "afio.h"
#include "nvic.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)

static void exti_callback(void){
    if (button_pressed() == 1){
        led_next_mode();
    }
}


int main(void) {
    systick_init(8000000 / 1000);
    led_init();
    button_init();
    afio_exti_select(0, GPIO_BANK_A);
    exti_init(0, 0, 1);
    nvic_set_priority(6, 2);
    nvic_enable_irq(6);
    exti_set_callback(exti_callback);
    while (1) {
        led_update();
    }
}