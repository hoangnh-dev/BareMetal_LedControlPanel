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
    Reset_Handler
};