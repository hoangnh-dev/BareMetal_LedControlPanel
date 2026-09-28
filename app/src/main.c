#include "stm32f103c8.h"
#include "led.h"
#include "button.h"
#include "cmd.h"
#include "led_cmd.h"

#define GPIOB_CRL    (*(volatile uint32_t*)0x40010C00)
#define GPIOB_BSRR   (*(volatile uint32_t*)0x40010C10)

static void exti_callback(void){
    if (button_pressed() == 1){
        led_next_mode();
        led_update();
    }
}


int main(void) {
    // systick_init(8000000 / 1000);
    led_init();
    button_init();
    afio_exti_select(0, GPIO_BANK_A);
    exti_init(0, 0, 1);

    nvic_set_priority(6, 2);
    nvic_enable_irq(6);
    exti_set_callback(exti_callback);
    timer_init(TIMER2);
    timer_set_prescaler(TIMER2, 7999);
    timer_enable_interrupt(TIMER2);
    nvic_set_priority(28, 4);
    nvic_enable_irq(28);

    uart_init(USART1, 115200);
    while (1) {
        cmd_run_menu(led_table);
    }
}

void tim2_irq_handler(void){
    if (TIMER2->SR & (1U << 0)){
        TIMER2->SR = 0;
        led_toggle();
    }
}