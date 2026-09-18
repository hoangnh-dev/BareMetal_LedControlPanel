#include "exti.h"
#include "afio.h"
#include "interrupt.h"

static exti_callback_t exti0_callback;

void afio_exti_select(uint8_t exti_number, uint8_t port){
    uint8_t index = exti_number >> 2;
    uint8_t shift = (exti_number & 3U) * 4U;

    AFIO->EXTICR[index] &= ~(0xFU << shift);
    AFIO->EXTICR[index] |= ((uint32_t)port << shift);
}
void exti_init(uint8_t exti_number, uint8_t falling, uint8_t rising){
    if (exti_number > 19U) return;
    if (rising) EXTI->RTSR |= (1U << exti_number);
    if (falling) EXTI->FTSR |= (1U << exti_number);

    EXTI->IMR |= (1U << exti_number);
}

uint8_t exti_get_pending(uint8_t exti_number){
    return (EXTI->PR & (1U << exti_number)) != 0U;
}

void exti_clear_pending(uint8_t exti_number){
    EXTI->PR = (1U << exti_number);
}

void exti_set_callback(exti_callback_t callback){
    exti0_callback = callback;
}

void exti0_irq_handler(void){
    if (exti_get_pending(0)) {
        exti_clear_pending(0);
        if (exti0_callback != 0)  exti0_callback();
    }
}