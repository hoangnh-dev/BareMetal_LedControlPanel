#ifndef RCC_H
#define RCC_H
#include <stdint.h>
typedef struct {
    volatile uint32_t RCC_CR;         // 0x00 - Clock control register
    volatile uint32_t RCC_CFGR;       // 0x04 - Clock configuration register
    volatile uint32_t RCC_CIR;        // 0x08 - Clock interrupt register
    volatile uint32_t RCC_APB2RSTR;   // 0x0C - APB2 peripheral reset register
    volatile uint32_t RCC_APB1RSTR;   // 0x10 - APB1 peripheral reset register
    volatile uint32_t RCC_AHBENR;     // 0x14 - AHB peripheral clock enable register
    volatile uint32_t RCC_APB2ENR;    // 0x18 - APB2 peripheral clock enable register
    volatile uint32_t RCC_APB1ENR;    // 0x1C - APB1 peripheral clock enable register
    volatile uint32_t RCC_BDCR;       // 0x20 - Backup domain control register
    volatile uint32_t RCC_CSR;        // 0x24 - Control/status register
} RCC_T;
#define RCC_BASE  0x40021000UL // RCC base address
#define RCC  ((RCC_T *)RCC_BASE) 
#endif