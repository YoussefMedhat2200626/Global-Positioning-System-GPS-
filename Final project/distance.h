// distance.h
#ifndef DISTANCE_H
#define DISTANCE_H
#define RADIUS_OF_EARTH_M 6371000.0  // Radius in meters
#define RADIUS_OF_EARTH_KM 6371.0
#define M_PI 3.14159265358979323846

double degToRad(double deg);
double haversine(double lat1, double lon1, double lat2, double lon2);
void calculateDistances(double currentLat, double currentLon, double buildings[][2], int numBuildings);
int findNearestBuildingIndex(int size);
double degToRad(double deg);

#endif
