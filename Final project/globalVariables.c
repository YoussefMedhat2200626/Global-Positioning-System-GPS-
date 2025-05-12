// globals.c
#include "globalVariables.h"

int fixed = 0;
char buffer[bufferLen] = {0};
char GPGGAbuffer[bufferLen] = {0};
char buffer6[7] = {0};
char GPGGALine[bufferLen] = {0};
double latitude = 0.0;
double longitude = 0.0;
int nearestIndex = 0;

char buildingnames[8][16] = {
    "Old building", "Library", "Football court", "mosque",
    "Credits Building", "Hall C", "Old building", "Hall A"
};

double buildings[8][2] = {
    {30.0640855, 31.2782688}, // Old building 7
    {30.0652731, 31.2800902}, // Library 3
    {30.063562833333336, 31.278835833333332}, // Football court 5
    {30.0644189, 31.280130},  // Mosque 0
    {30.0636829, 31.2783852}, // Credit Building 6
    {30.063715, 31.280700},   // Hall C 2
    {30.0646681, 31.2794224}, // Old building 4
    {30.06426, 31.2803}       // Hall A 1
};

double distances[8] = {0};
int numBuildings = 8;
