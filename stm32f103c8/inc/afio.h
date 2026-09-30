#ifndef AFIO_H
#define AFIO_H

#include <stdint.h>

typedef struct {
    volatile uint32_t EXTI0 : 4;     // 0, 4, 8, 12
    volatile uint32_t EXTI1 : 4;     // 1, 5, 9, 13
    volatile uint32_t EXTI2 : 4;     // 2, 6, 10, 14
    volatile uint32_t EXTI3 : 4;     // 3, 7, 11, 15
    volatile uint32_t       : 16;
} afio_exticr_t;

typedef struct {
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;

    union {
        volatile uint32_t EXTICR[4];
        volatile afio_exticr_t EXTICR_BITS[4];
    };
    uint32_t       : 32;
    volatile uint32_t MAPR2;
}afio_t;

#define AFIO ((afio_t *)0x40010000)

#endif