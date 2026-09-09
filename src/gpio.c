#include "gpio.h"

void GPIO_Init(gpio_t *port, uint8_t pin, gpio_mode_t  mode){
    if (pin < 8) {
        port->CRL &= ~(0xFU << (pin * 4)); 
        port->CRL |=  (mode << (pin * 4));
    }else {
        port->CRH &= ~(0xFU << ((pin - 8) * 4));
        port->CRH |= (mode << ((pin - 8) * 4));
    }
}

void GPIO_WritePin(gpio_t *port, uint8_t pin, uint8_t value){
    if (value) {
        port->BSRR = (1 << pin);
    }else {
        port->BSRR = (1 << (pin + 16));
    }
}