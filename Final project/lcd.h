#ifndef LCD_H
#define LCD_H

#include <stdint.h>

// Initializes the LCD
void LCD_Init(void);

// Sends a command to the LCD
void LCD_Command(uint8_t command);

// Clears the LCD screen
void LCD_Clear(void);

// Sends a single character to the LCD
void LCD_SendChar(char data);

// Converts an integer to a string
void itoa(int num, char *str, int base);

// Writes a string to the LCD
void LCD_WriteWord(const char* word);

// Writes a newline (moves the cursor to the next line)
void LCD_NewLine(void);

// Writes a double value to the LCD
void LCD_WriteDouble(double value);

// LCD Control lines
#define RS  (1U << 0)   // PD0
#define RW  (1U << 1)   // PD1
#define EN  (1U << 2)   // PD2

// LCD Data lines
#define D4  (1U << 4)   // PB4
#define D5  (1U << 5)   // PA5
#define D6  (1U << 6)   // PA6
#define D7  (1U << 7)   // PA7

#endif // LCD_H
