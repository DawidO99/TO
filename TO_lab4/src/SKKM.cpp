#include "SKKM.h"
#include "Strategies.h"
#include <QRandomGenerator>
#include <QTimer>
#include <algorithm> // std::sort

SKKM::SKKM() : eventCounter(0) {
    //Inicjalizacja jednostek, współrzędne są trochę przybliżone
    units.append(new Unit(1, "JRG-1", {50.063, 19.943}));
    units.append(new Unit(2, "JRG-2", {50.034, 19.936}));
    units.append(new Unit(3, "JRG-3", {50.076, 19.904}));
    units.append(new Unit(4, "JRG-4", {50.083, 20.046}));
    units.append(new Unit(5, "JRG-5", {50.091, 19.923}));
    units.append(new Unit(6, "JRG-6", {50.013, 20.007}));
    units.append(new Unit(7, "JRG-7", {50.028, 19.889}));
    units.append(new Unit(8, "SA PSP", {50.072, 20.038}));
    units.append(new Unit(9, "Skawina", {49.976, 19.825}));
    units.append(new Unit(10, "LSP Balice", {50.077, 19.789}));
}

void SKKM::createEvent() {
    Event e;
    e.id = ++eventCounter;
    e.active = true;
    
    //Losowanie pozycji zdarzenia
    double lat = MAP_MIN_LAT + (MAP_MAX_LAT - MAP_MIN_LAT) * QRandomGenerator::global()->generateDouble();
    double lon = MAP_MIN_LON + (MAP_MAX_LON - MAP_MIN_LON) * QRandomGenerator::global()->generateDouble();
    e.location = {lat, lon};

    //Wybór ilości sił z wykorzystaniem wzorca Strategia
    int typeRoll = QRandomGenerator::global()->bounded(100);
    std::shared_ptr<IDispatchStrategy> strategy;
    
    if (typeRoll < 30) { 
        e.type = PZ; 
        strategy = std::make_shared<FireStrategy>();
    } else { 
        e.type = MZ; 
        strategy = std::make_shared<LocalThreatStrategy>();
    }

    int carsNeeded = strategy->getRequiredCars();
    bool isFalse = (QRandomGenerator::global()->bounded(100) < 5); //5% szans na fałszywy alarm

    activeEvents.append(e);
    emit eventAdded(e);

    //Sortowanie jednostek wg odległości
    QList<Unit*> sortedUnits = units;
    std::sort(sortedUnits.begin(), sortedUnits.end(), [e](Unit* a, Unit* b){
        return calculateDistance(a->location, e.location) < calculateDistance(b->location, e.location);
    });

    //Algorytm dysponowania Iterator
    int sentTotal = 0;
    for(Unit* u : sortedUnits) {
        if(sentTotal >= carsNeeded) break;
        sentTotal += u->dispatchCars(carsNeeded - sentTotal, e.location, isFalse);
    }
    
    //Symulacja czasu trwania zdarzenia
    QTimer::singleShot(30000, this, [this, e]() {
        for(int i=0; i<activeEvents.size(); ++i) {
            if(activeEvents[i].id == e.id) {
                activeEvents.removeAt(i);
                emit eventRemoved(e.id);
                break;
            }
        }
    });
}