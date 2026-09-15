#ifndef LED_H
#define LED_H

#include "gpio.h"

typedef enum {
    LED_MODE_OFF = 0, //
    LED_MODE_ON,
    LED_MODE_BLINK_SLOW,
    LED_MODE_BLINK_FAST,
    LED_MODE_COUNT
}led_mode_t;

void led_init(void);
void led_next_mode(void);
void led_set_mode(led_mode_t mode);
void led_update(void);

#endif