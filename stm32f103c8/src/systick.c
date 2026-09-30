#include "systick.h"

#define SYSTICK_CSR_ENABLE_Pos      0U
#define SYSTICK_CSR_ENABLE_Msk      (1U << SYSTICK_CSR_ENABLE_Pos)

#define SYSTICK_CSR_TICKINT_Pos     1U
#define SYSTICK_CSR_TICKINT_Msk     (1U << SYSTICK_CSR_TICKINT_Pos)

#define SYSTICK_CSR_CLKSOURCE_Pos   2U
#define SYSTICK_CSR_CLKSOURCE_Msk   (1U << SYSTICK_CSR_CLKSOURCE_Pos)

static volatile uint32_t s_ticks = 0;

void systick_init(uint32_t ticks) {
    SYSTICK->RVR = ticks - 1;               
    SYSTICK->CVR = 0;                      
    SYSTICK->CSR = SYSTICK_CSR_ENABLE_Msk | SYSTICK_CSR_TICKINT_Msk | SYSTICK_CSR_CLKSOURCE_Msk; // ENABLE, TICKINT, CLKSOURCE
}

void systick_handler(void) {
    s_ticks++;
}

uint32_t systick_get_ticks(void) {
    return s_ticks;
}