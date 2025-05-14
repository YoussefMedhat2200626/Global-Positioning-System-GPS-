#ifndef UART5_H
#define UART5_H

// Initializes UART5 for communication via PE4 (Rx) and PE5 (Tx)
void UART5_Init(void);

// Receives a single character from UART5 (blocking)
char UART5_read(void);

#endif // UART5_H
