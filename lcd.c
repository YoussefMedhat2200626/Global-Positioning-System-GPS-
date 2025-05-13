#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "lcd.h"
#include "systick.h"


void LCD_EnablePulse(void) {
    GPIO_PORTD_DATA_R |= EN;
    DelayMs(1);
    GPIO_PORTD_DATA_R &= ~EN;
    DelayMs(1);
}

void LCD_SetData(unsigned char nibble) {
    // Clear all data bits first
    GPIO_PORTA_DATA_R &= ~(D5 | D6 | D7);
    GPIO_PORTB_DATA_R &= ~D4;

    // Set data bits
    if(nibble & 0x01) GPIO_PORTB_DATA_R |= D4;  // D4 -> PB4
    if(nibble & 0x02) GPIO_PORTA_DATA_R |= D5;  // D5 -> PA5
    if(nibble & 0x04) GPIO_PORTA_DATA_R |= D6;  // D6 -> PA6
    if(nibble & 0x08) GPIO_PORTA_DATA_R |= D7;  // D7 -> PA7
}

void LCD_Command(unsigned char cmd) {
    GPIO_PORTD_DATA_R &= ~RS;  // RS = 0 (Command)
    GPIO_PORTD_DATA_R &= ~RW;  // RW = 0 (Write)

    LCD_SetData(cmd >> 4);     // Send high nibble
    LCD_EnablePulse();

    LCD_SetData(cmd & 0x0F);   // Send low nibble
    LCD_EnablePulse();

    DelayMs(2);
}

void LCD_WriteChar(unsigned char data) {
    GPIO_PORTD_DATA_R |= RS;   // RS = 1 (Data)
    GPIO_PORTD_DATA_R &= ~RW;  // RW = 0 (Write)

    LCD_SetData(data >> 4);    // Send high nibble
    LCD_EnablePulse();

    LCD_SetData(data & 0x0F);  // Send low nibble
    LCD_EnablePulse();

    DelayMs(2);
}

void LCD_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x0B; // Enable Port A, B, D
    while((SYSCTL_PRGPIO_R & 0x0B) == 0);

    GPIO_PORTA_DIR_R |= (D5 | D6 | D7);
    GPIO_PORTA_DEN_R |= (D5 | D6 | D7);

    GPIO_PORTB_DIR_R |= D4;
    GPIO_PORTB_DEN_R |= D4;

    GPIO_PORTD_DIR_R |= (RS | RW | EN);
    GPIO_PORTD_DEN_R |= (RS | RW | EN);

    DelayMs(20);               // Wait for LCD power-up

    // Initialization sequence
    LCD_SetData(0x03);
    LCD_EnablePulse();
    DelayMs(5);

    LCD_SetData(0x03);
    LCD_EnablePulse();
    DelayMs(1);

    LCD_SetData(0x03);
    LCD_EnablePulse();
    DelayMs(1);

    LCD_SetData(0x02);         // Set 4-bit mode
    LCD_EnablePulse();

    LCD_Command(0x28);         // Function Set: 4-bit, 2 Line, 5x8 dots
    LCD_Command(0x0C);         // Display ON, Cursor OFF
    LCD_Command(0x06);         // Entry Mode
    LCD_Command(0x01);         // Clear Display
    DelayMs(2);
}
void LCD_WriteWord(const char* word) {
    while (*word != '\0') {    // Loop until the null-terminator is found
        LCD_WriteChar(*word);  // Write each character to the LCD
        word++;                // Move to the next character
    }
}
// LCD Clear function
void LCD_Clear(void) {
    LCD_Command(0x01);         // Command to clear the display
    DelayMs(2);                // Wait for clear to complete
}

// LCD New Line function
void LCD_NewLine(void) {
    LCD_Command(0xC0);         // Command to move cursor to the second line (0xC0 = 0b11000000)
}

// LCD Write Double (floating point) function
void LCD_WriteDouble(double value) {
    char buffer[20];  // Buffer to hold the formatted string

    // Convert double to string with 6 decimal places
    sprintf(buffer, "%.6f", value);

    // Write the string to the LCD
    LCD_WriteWord(buffer);
}
