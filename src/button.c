#include "button.h"

void button_init(gpio_t *port, uint8_t pin) {
    GPIO_Init(port, pin, GPIO_MODE_INPUT_PUPD);   
}

uint8_t button_read(gpio_t *port, uint8_t pin) {
    return (port->IDR >> pin) & 1;  
}