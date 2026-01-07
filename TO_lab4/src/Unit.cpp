#include "Unit.h"

Unit::Unit(int id, QString name, Location loc) : id(id), name(name), location(loc) {
    for(int i=0; i<5; ++i) {
        cars.append(new Car(i+1, id, loc));
    }
}

//Sprawdzamy, które auta są wolne
int Unit::dispatchCars(int countNeeded, Location target, bool isFalseAlarm) {
    int dispatched = 0;
    for (Car* car : cars) {
        if (dispatched >= countNeeded) break;
        if (car->isFree()) {
            car->dispatch(target, isFalseAlarm);
            dispatched++;
        }
    }
    return dispatched;
}