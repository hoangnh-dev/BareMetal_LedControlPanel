#include "timer.h"
#include "rcc.h"
#include "interrupt.h"

void timer_clock_enable(volatile timer_t *tim){
    if (tim == TIMER2) {
        RCC->RCC_APB1ENR |= (1U << 0);
    }
    else if (tim == TIMER3) {
        RCC->RCC_APB1ENR |= (1U << 1);
    }
    else if (tim == TIMER4) {
        RCC->RCC_APB1ENR |= (1U << 2);
    }
}

void timer_init(volatile timer_t *tim){
    timer_clock_enable(tim);

    tim->CR1 = 0;
    tim->CNT = 0;
    tim->SR = 0;
}
void timer_set_prescaler(volatile timer_t *tim, uint32_t psc){
    tim->PSC = psc;
}
void timer_set_period(volatile timer_t *tim, uint32_t arr){
    tim->ARR = arr;
}
void timer_reset_counter(volatile timer_t *tim){
    tim->CNT = 0;
}
void timer_enable(volatile timer_t *tim){
    tim->CR1 |= (1U << 0);
}
void timer_disable(volatile timer_t *tim){
    tim->CR1 &= ~(1U << 0);
}
void timer_enable_interrupt(volatile timer_t *tim){
    tim->DIER |= (1U << 0);    
}

void timer_disable_interrupt(volatile timer_t *tim){
    tim->DIER &= ~(1U << 0); 
}
