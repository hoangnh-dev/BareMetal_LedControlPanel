#include "systick.h"

static volatile uint32_t s_ticks = 0;

void systick_init(uint32_t ticks) {
    SYSTICK->RVR = ticks - 1;               
    SYSTICK->CVR = 0;                      
    SYSTICK->CSR = (1 << 0) | (1 << 1) | (1 << 2); // ENABLE, TICKINT, CLKSOURCE
}

void systick_handler(void) {
    s_ticks++;
}

uint32_t systick_get_ticks(void) {
    return s_ticks;
}