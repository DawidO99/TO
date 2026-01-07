#ifndef LOCATION_H
#define LOCATION_H

#include <QtMath>

//Granice Mapy
const double MAP_MIN_LAT = 49.958550;
const double MAP_MAX_LAT = 50.154564;
const double MAP_MIN_LON = 19.688292;
const double MAP_MAX_LON = 20.060000;

//Struktura współrzędnych geograficznych
struct Location {
    double lat; //szerokość na N/S od równika
    double lon; //długość na W/E od południka
};

//Typy zdarzeń
enum EventType { MZ, PZ, AF }; //Miejscowe Zagrożenia, Pożary, Alarmy Fałszywe

struct Event {
    int id;
    EventType type;
    Location location;
    bool active;
};

//Funkcja do obliczania odległości między eventem a najbliższą jednostką (wzór Haversine)
inline double calculateDistance(Location l1, Location l2) {
    const double R = 6371.0; //Promień Ziemi w km
    double dLat = qDegreesToRadians(l2.lat - l1.lat);
    double dLon = qDegreesToRadians(l2.lon - l1.lon);
    double a = qSin(dLat / 2) * qSin(dLat / 2) +
               qCos(qDegreesToRadians(l1.lat)) * qCos(qDegreesToRadians(l2.lat)) *
               qSin(dLon / 2) * qSin(dLon / 2);
    double c = 2 * qAtan2(qSqrt(a), qSqrt(1 - a));
    return R * c;
}

#endif