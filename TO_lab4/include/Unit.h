#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QList>
#include "Car.h"
#include "Location.h"

//Reprezentacja jednostki
class Unit {
public:
    int id;
    QString name;
    Location location;
    QList<Car*> cars;

    Unit(int id, QString name, Location loc);
    int dispatchCars(int countNeeded, Location target, bool isFalseAlarm);
};

#endif