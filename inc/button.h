#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h"

void button_init(gpio_t *port, uint8_t pin);
uint8_t button_read(gpio_t *port, uint8_t pin);

#endif