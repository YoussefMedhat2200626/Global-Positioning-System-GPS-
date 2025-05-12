#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "uart3.h"

// Add the definition of UART3_Init
void UART3_Init(void) {
    // 1. Enable Clocks
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R3;      // Enable UART3 clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;      // Enable GPIOC clock
    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R3) == 0U); // Wait for UART3 clock to be ready
    while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R2) == 0U); // Wait for GPIOC clock to be ready

    // 2. Disable UART for configuration
    UART3_CTL_R &= ~UART_CTL_UARTEN;    // Clear UARTEN bit


    UART3_IBRD_R = 104;                 // Integer Baud Rate Divisor
    UART3_FBRD_R = 11;                  // Fractional Baud Rate Divisor

    // 4. Set Line Control (Frame Format)
    UART3_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);  // 8-bit data, FIFO Enabled

    // 5. Enable UART and TX 
    UART3_CTL_R |= (UART_CTL_UARTEN | UART_CTL_TXE );


    // 6. Configure GPIO Pins PC6 (U3Rx) and PC7 (U3Tx) for UART Alternate Function
    GPIO_PORTC_AFSEL_R |= ( (1U << 6) | (1U << 7) ); // Enable alternate function for PC6 and PC7

    // Set PCTL for PC6 and PC7 to select UART3 function.

    GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0x00FFFFFFU) | 0x11000000U;

    GPIO_PORTC_DEN_R |= ( (1U << 6) | (1U << 7) );   // Digital enable for PC6, PC7
    GPIO_PORTC_AMSEL_R &= ~( (1U << 6) | (1U << 7) ); // Disable analog function on PC6, PC7
}


void UART3_SendByte(uint8_t data) {
    // Wait until the Transmit FIFO is not full (TXFF flag in UART3_FR_R is 0)
    while((UART3_FR_R & UART_FR_TXFF) != 0U); 
    UART3_DR_R = data; // Write the byte to UART3 Data Register to send
}
