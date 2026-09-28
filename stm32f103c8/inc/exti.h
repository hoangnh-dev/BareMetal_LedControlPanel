#ifndef EXTI_H
#define EXTI_H
#include <stdint.h>

typedef void (*exti_callback_t)(void);

typedef struct {
    uint32_t IMR;    // Interrupt mask register
    uint32_t EMR;    // Event mask register
    uint32_t RTSR;   // Rising trigger selection register
    uint32_t FTSR;   // Falling trigger selection register
    uint32_t SWIER;  // Software interrupt event register
    uint32_t PR;     // Pending register
} exti_t;

#define EXTI ((volatile exti_t *)0x40010400)

void exti_init(uint8_t  exti_number, uint8_t falling, uint8_t rising);
uint8_t exti_get_pending(uint8_t  exti_number);
void exti_clear_pending(uint8_t  exti_number);
void exti_set_callback(exti_callback_t callback);
void afio_exti_select(uint8_t exti_number, uint8_t port);

#endif