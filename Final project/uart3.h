#ifndef UART3_H
#define UART3_H

#include <stdint.h>

// Initializes UART3 with PC6 (Rx) and PC7 (Tx)
void UART3_Init(void);

// Sends a single byte over UART3
void UART3_SendByte(uint8_t data);

#endif // UART3_H
