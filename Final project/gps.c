#include "tm4c123gh6pm.h"
#include "gps.h"
#include "uart5.h"
#include "string.h"
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "globalVariables.h"
#include "systick.h"
#include "UART0.h"

extern int fixed;
extern char buffer[bufferLen];
extern char buffer6[7];
extern char GPGGALine[bufferLen];
extern char GPGGAbuffer[bufferLen];
extern double latitude;
extern double longitude;

void GPSbufferUpdate(void){
	int flag=0;
	char c;
	int i;
	
	while(flag!=1){
				for(i =0;i<bufferLen;i++){
					c = UART5_read();
					if(c=='\n' || c=='\r'){ 
						break;
					}
					else{
						buffer[i]=c;
						if(i<6)buffer6[i]=c;
					}
				}
				
				if(strcmp(buffer6, "$GPGGA")==0){
					strcpy(GPGGALine,buffer);
					flag=1;
				}
	}

}



double  degreeToDecimal(double value){
    double decimal = (int)( value/100);
    double minuite = value - decimal*100;
    decimal += (minuite / 60);
    
    return decimal;
    }

		void PortFF_Int(void){

	SYSCTL_RCGCGPIO_R |=0x20;
	while ((SYSCTL_PRGPIO_R&0x20)==0);
	GPIO_PORTF_LOCK_R  =	GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R |=0x1F;
	GPIO_PORTF_AMSEL_R &= ~(0x1F);
	GPIO_PORTF_AFSEL_R &= ~(0x1F);
	GPIO_PORTF_PCTL_R &= 0xFFF00000;
	GPIO_PORTF_DEN_R |= 0x1F;
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_PUR_R |= 0x11;

}

void readNewDataFromGPS(void) {
    char *ptr;
    char *token;

    // Update the GPS buffer
    GPSbufferUpdate();  // Get new GPS data

    // Start tokenizing the GPGGA sentence
    UART0_SendString("GPGGA Sentence: ");
    UART0_SendString(GPGGALine);  // Output full raw GPGGA sentence
    UART0_SendString("\r\n");

    // Tokenize the sentence and output all fields
    token = strtok(GPGGALine, ","); // Tokenize the first part ($GPGGA)
    token = strtok(NULL, ",");       // Skip time (hhmmss)
    token = strtok(NULL, ",");       // Latitude

 // After parsing raw values
if (token != NULL) {
    latitude = strtod(token, &ptr);
}
token = strtok(NULL, ",");  // N/S
if (token != NULL) {
    if (token[0] == 'S') {
        latitude = -latitude;
    }
}

// Convert to decimal degrees
latitude = degreeToDecimal(fabs(latitude)) * (latitude < 0 ? -1 : 1);

// Parse longitude
token = strtok(NULL, ",");
if (token != NULL) {
    longitude = strtod(token, &ptr);
}
token = strtok(NULL, ",");  // E/W
if (token != NULL) {
    if (token[0] == 'W') {
        longitude = -longitude;
    }
}

// Convert to decimal degrees
longitude = degreeToDecimal(fabs(longitude)) * (longitude < 0 ? -1 : 1);


					

    // Cleanly output latitude and longitude
    UART0_SendString("Latitude: ");
    UART0_SendDouble(latitude, 6);
    UART0_SendString("\r\nLongitude: ");
    UART0_SendDouble(longitude, 6);
    UART0_SendString("\r\n");
}
