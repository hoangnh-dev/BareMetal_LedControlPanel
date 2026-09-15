#include "led.h"
#include "systick.h"

#define led_pin 2

static led_mode_t currentMode = LED_MODE_OFF;
static uint8_t led_state = 0;
static uint32_t last_toggle = 0;

void led_init(void) {
    currentMode = LED_MODE_OFF;
    gpio_init(GPIOB, led_pin, GPIO_MODE_OUTPUT_PP_10MHZ, GPIO_BANK_B);
}
void led_set_mode(led_mode_t mode) {
	if (mode >= LED_MODE_COUNT) return;
    currentMode = mode;
}
void led_next_mode(void) {
    currentMode = (currentMode + 1) % LED_MODE_COUNT;
}

void led_update_state(void){
    gpio_write(GPIOB, led_pin, led_state);
}

void led_toggle(void){
    led_state = !led_state;
    led_update_state();
}
void led_blink(uint32_t interval_ms){
    if ((systick_get_ticks() - last_toggle) >= 500) {
        led_toggle();
        last_toggle = systick_get_ticks();
    }
}

void led_update(void) {
    switch (currentMode) {
        case LED_MODE_OFF:
        case LED_MODE_ON:{
            led_state = currentMode;
            led_update_state();
        }break;
        case LED_MODE_BLINK_SLOW:{
            led_blink(500);
        }break;
        case LED_MODE_BLINK_FAST:{
            led_blink(100);
        }break;
        default: break;
    }
}