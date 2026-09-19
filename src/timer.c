#include "timer.h"

void timer_init(volatile timer_t *tim){
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