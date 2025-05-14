#include "systick.h"
#include "tm4c123gh6pm.h"

void SysTick_Init(void) {
    // Step 1: Disable SysTick
    NVIC_ST_CTRL_R = 0;

    // Step 2: Set reload value for 1ms (16,000 ticks at 16 MHz)
    NVIC_ST_RELOAD_R = 16000 - 1;

    // Step 3: Clear current value
    NVIC_ST_CURRENT_R = 0;

    // Step 4: Enable SysTick with system clock, no interrupt
    NVIC_ST_CTRL_R = 0x05; // ENABLE=1, CLK_SRC=1, INTEN=0
}

void DelayMs(unsigned long delay) {
		unsigned long i;
    for ( i= 0; i < delay; i++) {
        while ((NVIC_ST_CTRL_R & 0x00010000) == 0) {
            // Wait until COUNT flag is set
        }
    }
}
