#include <math.h>
#include <stdio.h>
#include "globalVariables.h"
#include "uart0.h"
#include "distance.h"



double haversine(double lat1, double lon1, double lat2, double lon2) {
					double dLat, dLon, a, c;

					lat1 = degToRad(lat1);
					lon1 = degToRad(lon1);
					lat2 = degToRad(lat2); 
					lon2 = degToRad(lon2);

dLat = lat2 - lat1;
dLon = lon2 - lon1;

a = sin(dLat / 2) * sin(dLat / 2) +
    cos(lat1) * cos(lat2) *
    sin(dLon / 2) * sin(dLon / 2);

c = 2 * atan2(sqrt(a), sqrt(1 - a));

return RADIUS_OF_EARTH_M * c;  // distance in meters

}



void calculateDistances(double currentLat, double currentLon, double buildings[][2], int numBuildings) {
    char msg[50];
    int i;
    double buildingLat, buildingLon;

    for (i = 0; i < numBuildings; i++) {
        buildingLat = buildings[i][0];
        buildingLon = buildings[i][1];
        distances[i] = haversine(currentLat, currentLon, buildingLat, buildingLon);
        sprintf(msg, "Building %d: ", i + 1);
				UART0_SendString(msg);
				UART0_SendDouble(distances[i], 2);  // now this is in METERS
				UART0_SendString(" m\r\n");
    }
}
int findNearestBuildingIndex(int size) {
    int minIndex = 0;
		int i;
    for (i= 1; i < size; i++) {
        if (distances[i] < distances[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

double degToRad(double deg) {
    return deg * (M_PI / 180.0);
}
