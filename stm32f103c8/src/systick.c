#include "systick.h"

#define SYSTICK_CSR_ENABLE_Pos      0U
#define SYSTICK_CSR_ENABLE_Msk      (1U << SYSTICK_CSR_ENABLE_Pos)

#define SYSTICK_CSR_TICKINT_Pos     1U
#define SYSTICK_CSR_TICKINT_Msk     (1U << SYSTICK_CSR_TICKINT_Pos)

#define SYSTICK_CSR_CLKSOURCE_Pos   2U
#define SYSTICK_CSR_CLKSOURCE_Msk   (1U << SYSTICK_CSR_CLKSOURCE_Pos)

static volatile uint32_t s_ticks = 0U;
static void (*systick_callback)(void);
static uint32_t callback_deadline;

void systick_init(uint32_t ticks) {
    SYSTICK->RVR = ticks - 1;               
    SYSTICK->CVR = 0U;                      
    SYSTICK->CSR = SYSTICK_CSR_ENABLE_Msk | SYSTICK_CSR_TICKINT_Msk | SYSTICK_CSR_CLKSOURCE_Msk; // ENABLE, TICKINT, CLKSOURCE
}

uint32_t systick_get_ticks(void) {
    return s_ticks;
}

void systick_set_callback(void (*callback)(void), uint32_t delay_ms){
    systick_callback = callback;
    callback_deadline = systick_get_ticks() + delay_ms;
}

void systick_handler(void) {
    s_ticks++;
    if (callback_deadline != 0U && s_ticks >= callback_deadline) {
        if (systick_callback != NULL) systick_callback();
        callback_deadline = 0U;
    }
}