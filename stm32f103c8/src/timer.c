#include "timer.h"
#include "rcc.h"
#include "interrupt.h"

/* RCC_APB1ENR bit definitions */
#define RCC_APB1ENR_TIM2EN_Pos   0U
#define RCC_APB1ENR_TIM2EN_Msk   (1U << RCC_APB1ENR_TIM2EN_Pos)
#define RCC_APB1ENR_TIM3EN_Pos   1U
#define RCC_APB1ENR_TIM3EN_Msk   (1U << RCC_APB1ENR_TIM3EN_Pos)
#define RCC_APB1ENR_TIM4EN_Pos   2U
#define RCC_APB1ENR_TIM4EN_Msk   (1U << RCC_APB1ENR_TIM4EN_Pos)

/* TIMx_CR1 bit definitions */
#define TIM_CR1_CEN_Pos          0U
#define TIM_CR1_CEN_Msk          (1U << TIM_CR1_CEN_Pos)

/* TIMx_DIER bit definitions */
#define TIM_DIER_UIE_Pos         0U
#define TIM_DIER_UIE_Msk         (1U << TIM_DIER_UIE_Pos)

void timer_clock_enable(timer_t *tim){
    if (tim == TIMER2) {
        RCC->RCC_APB1ENR |= RCC_APB1ENR_TIM2EN_Msk;;
    }
    else if (tim == TIMER3) {
        RCC->RCC_APB1ENR |= RCC_APB1ENR_TIM3EN_Msk ;
    }
    else if (tim == TIMER4) {
        RCC->RCC_APB1ENR |= RCC_APB1ENR_TIM4EN_Msk ;
    }
}

void timer_init(timer_t *tim){
    timer_clock_enable(tim);

    tim->CR1 = 0;
    tim->CNT = 0;
    tim->SR = 0;
}
void timer_set_prescaler(timer_t *tim, uint32_t psc){
    tim->PSC = psc;
}
void timer_set_period(timer_t *tim, uint32_t arr){
    tim->ARR = arr;
}
void timer_reset_counter(timer_t *tim){
    tim->CNT = 0;
}
void timer_enable(timer_t *tim){
    tim->CR1 |= TIM_CR1_CEN_Msk;
}
void timer_disable(timer_t *tim){
    tim->CR1 &= ~TIM_CR1_CEN_Msk;
}
void timer_enable_interrupt(timer_t *tim){
    tim->DIER |= TIM_DIER_UIE_Msk;    
}

void timer_disable_interrupt(timer_t *tim){
    tim->DIER &= ~TIM_DIER_UIE_Msk; 
}
