// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H

#define bufferLen 100

extern int fixed;
extern char buffer[bufferLen];
extern char GPGGAbuffer[bufferLen];
extern char buffer6[7];
extern char GPGGALine[bufferLen];
extern double latitude;
extern double longitude;
extern int nearestIndex;
extern char buildingnames[8][16];
extern double buildings[8][2];
extern double distances[8];
extern int numBuildings;

#endif
