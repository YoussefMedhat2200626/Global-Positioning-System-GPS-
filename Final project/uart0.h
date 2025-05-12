#ifndef UART0_H
#define UART0_H

void UART0_Init(void);
// Sends a single character over UART0
void UART0_SendChar(char c);

// Sends a null-terminated string over UART0
void UART0_SendString(const char *str);

// Sends an integer as a string over UART0
void UART0_SendNumber(int num);

// Sends a double as a string over UART0
void UART0_SendDouble(double num, int decimalPlaces);

#endif // UART0_H
