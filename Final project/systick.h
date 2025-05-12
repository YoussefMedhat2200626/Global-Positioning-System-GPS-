// systick.h
// SysTick delay functions for TM4C123GH6PM

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

// Initializes SysTick to generate 1ms delay at 16 MHz clock
void SysTick_Init(void);

// Delays execution by the specified number of milliseconds (blocking)
void DelayMs(unsigned long delay);

#endif // SYSTICK_H
