#ifndef AFIO_H
#define AFIO_H

#include <stdint.h>

typedef struct {
    uint32_t EXTI0 : 4;     // 0, 4, 8, 12
    uint32_t EXTI1 : 4;     // 1, 5, 9, 13
    uint32_t EXTI2 : 4;     // 2, 6, 10, 14
    uint32_t EXTI3 : 4;     // 3, 7, 11, 15
    uint32_t       : 16;
} afio_exticr_t;

typedef struct {
    uint32_t EVCR;
    uint32_t MAPR;

    union {
        uint32_t EXTICR[4];
        afio_exticr_t EXTICR_BITS[4];
    };
    uint32_t       : 32;
    uint32_t MAPR2;
}afio_t;

#define AFIO ((volatile afio_t *)0x40010000)

#endif