#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
typedef struct {
    volatile uint32_t CSR;   // Control and Status Register
    volatile uint32_t RVR;   // Reload Value Register
    volatile uint32_t CVR;   // Current Value Register
    volatile uint32_t CALIB; // Calibration Register
} systick_t;

#define SYSTICK ((systick_t *) 0xE000E010UL) // SysTick base address

void systick_init(uint32_t ticks);
void systick_handler(void);
uint32_t systick_get_ticks(void);
#endif