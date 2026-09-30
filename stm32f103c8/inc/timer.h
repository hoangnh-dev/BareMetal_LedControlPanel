#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CR1;   // Control Register 1
    volatile uint32_t CR2;   // Control Register 2
    volatile uint32_t SMCR;  //  Slave Mode Control Register
    volatile uint32_t DIER;  // DMA/Interrupt Enable Register
    volatile uint32_t SR;    // Status Register
    volatile uint32_t EGR;   // Event Generation Register
    volatile uint32_t CCMR1; // Capture/Compare Mode Register 1 (Ch 1 & 2)
    volatile uint32_t CCMR2; //  Capture/Compare Mode Register 2 (Ch 3 & 4)
    volatile uint32_t CCER;  // Capture/Compare Enable Register
    volatile uint32_t CNT;   // Counter Register
    volatile uint32_t PSC;   // Prescaler
    volatile uint32_t ARR;   // Auto-reload Register
    volatile uint32_t RCR;   // Repetition Counter (TIM1/TIM8 only)
    volatile uint32_t CCR1;  // Capture/compare register 1
    volatile uint32_t CCR2;  // Capture/compare register 2
    volatile uint32_t CCR3;  // Capture/compare register 3
    volatile uint32_t CCR4;  // Capture/compare register 4
    volatile uint32_t BDTR;  // Break and dead-time register (TIM1/TIM8 only)
    volatile uint32_t DCR;   // DMA control register
    volatile uint32_t DMAR;  // DMA address for full transfer
} timer_t;

// Base addresses for STM32F103 Timers
#define TIMER1 ((timer_t *)0x40012C00)  // Advanced control timer
#define TIMER2 ((timer_t *)0x40000000)  // General-purpose timer
#define TIMER3 ((timer_t *)0x40000400)  // General-purpose timer
#define TIMER4 ((timer_t *)0x40000800)  // General-purpose timer

void timer_init(timer_t *tim);
void timer_set_prescaler(timer_t *tim, uint32_t psc);
void timer_set_period(timer_t *tim, uint32_t arr);
void timer_reset_counter(timer_t *tim);
void timer_enable(timer_t *tim);
void timer_disable(timer_t *tim);
void timer_enable_interrupt(timer_t *tim);
void timer_disable_interrupt(timer_t *tim);

#endif

