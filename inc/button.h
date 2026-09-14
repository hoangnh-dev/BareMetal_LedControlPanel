#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h"

void button_init(void);
uint8_t button_pressed(void);

#endif