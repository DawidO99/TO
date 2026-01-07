#ifndef CAR_H
#define CAR_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <memory>
#include "Location.h"

class Car; //Forward declaration

//Interfejs wzorca Stan
class CarState {
public:
    virtual ~CarState() = default;
    virtual void handle(Car* car) = 0;
    virtual QString name() const = 0;
    virtual bool isFree() const { return false; }
};

//Klasa Samochodu (Context)
class Car : public QObject {
    Q_OBJECT
public:
    int id;
    int parentUnitId;
    std::shared_ptr<CarState> state;

    //Dane do wizualizacji
    Location currentPos;
    Location targetPos;
    double progress; //0.0 - 1.0

    Car(int id, int unitId, Location startLoc);

    void setState(std::shared_ptr<CarState> newState);
    bool isFree() const;
    void dispatch(Location target, bool falseAlarm);

    signals:
        void stateChanged(int carId, QString stateName);
    void positionChanged(); //Sygnał dla GUI
};

#endif