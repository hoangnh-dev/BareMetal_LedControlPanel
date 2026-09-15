#include "button.h"
#define btn_pin 0

void button_init() {
    gpio_init(GPIOA, btn_pin, GPIO_MODE_INPUT_PUPD, GPIO_BANK_A);   
}

uint8_t button_pressed() {
    return gpio_read(GPIOA, btn_pin);  
}