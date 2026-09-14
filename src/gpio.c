#include "gpio.h"

void gpio_init(gpio_t *port, uint8_t pin, gpio_mode_t  mode){
    if (pin < 8) {
        port->CRL &= ~(0xFU << (pin * 4)); 
        port->CRL |=  (mode << (pin * 4));
    }else {
        port->CRH &= ~(0xFU << ((pin - 8) * 4));
        port->CRH |= (mode << ((pin - 8) * 4));
    }
}

void gpio_write(gpio_t *port, uint8_t pin, uint8_t value){
    if (value) {
        port->BSRR = (1 << pin);
    }else {
        port->BSRR = (1 << (pin + 16));
    }
}

uint8_t gpio_read(gpio_t *port, uint8_t pin) {
    return (port->IDR >> pin) & 1;  
}