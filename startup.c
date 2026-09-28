#include "systick.h"
#include "interrupt.h"
// 16 standard and 91 STM32-specific handlers
#define NUM_CORE_HANDLERS 16
#define NUM_STM32_HANDLERS 91

extern unsigned long _estack;

int main(void);
void Reset_Handler(void);


// Startup code
__attribute__((noreturn))
void Reset_Handler(void)
{
    extern long _sbss, _ebss;
    extern long _sdata, _edata, _sidata;

    // Clear .bss
    for (long *dst = &_sbss; dst < &_ebss; dst++)
        *dst = 0;

    // Copy .data from Flash to RAM
    for (long *dst = &_sdata, *src = &_sidata;
         dst < &_edata;
         dst++, src++)
        *dst = *src;

    main();

    // Should never be reached
    for (;;)
        ;
}


// Vector table
__attribute__((section(".isr_vector")))
void (*const tab[NUM_CORE_HANDLERS + NUM_STM32_HANDLERS])(void) =
{
    (void (*)(void))(&_estack),
    Reset_Handler,
    0,                    // NMI_Handler 
    0,                    // HardFault_Handler 
    0,                    // MemManage_Handler
    0,                    // BusFault_Handler
    0,                    // UsageFault_Handler
    0, 0, 0, 0,            // Reserved
    0,                    // SVC_Handler
    0,                    // DebugMon_Handler
    0,                    // Reserved
    0,                    // PendSV_Handler
    systick_handler,      // SysTick
    0,                    // IRQ0  - WWDG
    0,                    // IRQ1  - PVD
    0,                    // IRQ2  - TAMPER
    0,                    // IRQ3  - RTC
    0,                    // IRQ4  - FLASH
    0,                    // IRQ5  - RCC
    exti0_irq_handler,    // IRQ6  - EXTI0
    0,                    // IRQ7  - EXTI1
    0,                    // IRQ8  - EXTI2
    0,                    // IRQ9  - EXTI3
    0,                    // IRQ10 - EXTI4
    0,                    // IRQ11 - DMA1 Channel
    0,                    // IRQ12 - DMA1 Channe2
    0,                    // IRQ13 - DMA1 Channe3
    0,                    // IRQ14 - DMA1 Channe4
    0,                    // IRQ15 - DMA1 Channe5
    0,                    // IRQ16 - DMA1 Channe6
    0,                    // IRQ17 - DMA1 Channe7
    0,                    // IRQ18 - ADC1 and ADC2
    0,                    // IRQ19 - CAN1 TX 
    0,                    // IRQ20 - CAN1 RX0 
    0,                    // IRQ21 - CAN1 RX1 
    0,                    // IRQ22 - CAN1 SCE
    0,                    // IRQ23 - EXTI Line[9:5]
    0,                    // IRQ24 - TIM1 Break interrupt
    0,                    // IRQ25 - TIM1 Update interrupt
    0,                    // IRQ26 - TIM1 Trigger and Commutation
    0,                    // IRQ27 - TIM1 Capture Compare
    tim2_irq_handler,     // IRQ28 - TIM2
};