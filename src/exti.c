#include "exti.h"
#include "afio.h"

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