#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "string.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "UART0.h"
#include "uart5.h"
#include "uart3.h"
#include "gps.h"
#include "lcd.h"
#include "mp3.h"
#include "systick.h"
#include "distance.h"
#include "globalVariables.h"

int main(void) {
    volatile int i;  // <-- declare here at the start of the block

		SysTick_Init();
    UART0_Init();
		UART1_Init();
		UART5_Init();
		UART3_Init();
		LCD_Init();
    while(1) {
			
			GPSbufferUpdate();
			readNewDataFromGPS();
      UART0_SendString(GPGGAbuffer);     // New line for readability
			LCD_WriteWord("Nearest Building");
			LCD_NewLine();
			
			
			// After updating GPS and displaying coordinates:
			calculateDistances(latitude, longitude, buildings, numBuildings);
			
			LCD_WriteWord(buildingnames[findNearestBuildingIndex(numBuildings)]);
			MP3_PlayBuilding();
			
			UART3_SendByte(findNearestBuildingIndex(numBuildings));
			
			DelayMs(3000); // Simple delay
			LCD_Clear();
    }
}

