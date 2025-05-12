#include "UART0.h"
#include "tm4c123gh6pm.h"

void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= 0x01;          // Enable UART0 clock
    SYSCTL_RCGCGPIO_R |= 0x01;          // Enable GPIOA clock

    UART0_CTL_R &= ~UART_CTL_UARTEN;    // Disable UART for config
    UART0_IBRD_R = 104;                 // Baud Rate Integer (16MHz, 9600bps)
    UART0_FBRD_R = 11;                  // Baud Rate Fraction
    UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);  // 8-bit, FIFO
    UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE);  // Enable UART

    GPIO_PORTA_AFSEL_R |= 0x03;         // PA0, PA1 alternate function
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011; // UART0
    GPIO_PORTA_DEN_R |= 0x03;           // Digital enable PA0, PA1
    GPIO_PORTA_AMSEL_R &= ~0x03;        // Disable analog on PA0, PA1
}

// Send a single character over UART0
void UART0_SendChar(char c) {
    while ((UART0_FR_R & UART_FR_TXFF) != 0);  // Wait until TX buffer is not full
    UART0_DR_R = c;
}

// Send a null-terminated string over UART0
void UART0_SendString(const char *str) {
    while (*str) {
        UART0_SendChar(*str++);
    }
}

void UART0_SendNumber(int num) {
    char buffer[10];
    int i = 0;

    if(num == 0) {
        UART0_SendChar('0');
        return;
    }

    if(num < 0) {                       // Handle negative numbers
        UART0_SendChar('-');
        num = -num;
    }

    while(num > 0) {                    // Convert number to string (reverse order)
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i--) {                        // Send digits in correct order
        UART0_SendChar(buffer[i]);
    }
}

void UART0_SendDouble(double num, int decimalPlaces) {
    int intPart;
    double fraction;
    int i;
    int fracPart;

    if(num < 0) {  // Handle negative numbers
        UART0_SendChar('-');
        num = -num;
    }

    intPart = (int)num;                    // Integer part
    fraction = num - intPart;              // Fractional part

    UART0_SendNumber(intPart);             // Send integer part
    UART0_SendChar('.');                   // Decimal point

    for(i = 0; i < decimalPlaces; i++) {   // Scale fraction
        fraction *= 10;
    }

    fracPart = (int)(fraction + 0.5);      // Round
    UART0_SendNumber(fracPart);            // Send fractional part
}
