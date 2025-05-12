#ifndef GPS_H
#define GPS_H

#include <stdint.h>



// Reads GPS data into buffer and extracts GPGGA sentence
void GPSbufferUpdate(void);

// Loops until a GPS fix is obtained (GPGGA valid fix)
void GPS_Fixed(void);

// Converts NMEA degree format to decimal degrees
double degreeToDecimal(double value);

// Initializes Port F with pull-ups for switches and outputs for LEDs
void PortFF_Int(void);

void GPS_Fixed(void);

void readNewDataFromGPS(void);
#endif // GPS_H
