#include "Car.h"
#include <QRandomGenerator>

//Definicje konkretnych stanów
class FreeState : public CarState {
public:
    void handle(Car* car) override { car->progress = 0; }
    QString name() const override { return "WOLNY"; }
    bool isFree() const override { return true; }
};

//Bazowa klasa dla stanów animowanych (Dojazd/Powrót)
class AnimationState : public CarState {
protected:
    QTimer* animTimer;
    int durationMs;
    int elapsed;
public:
    AnimationState(int ms) : durationMs(ms), elapsed(0) {}
    
    virtual void onFinish(Car* car) = 0;

    void handle(Car* car) override {
        elapsed = 0;
        animTimer = new QTimer(car);
        QObject::connect(animTimer, &QTimer::timeout, car, [this, car]() {
            elapsed += 16;
            car->progress = (double)elapsed / durationMs;
            if (car->progress > 1.0) car->progress = 1.0;

            car->positionChanged();

            if (elapsed >= durationMs) {
                car->currentPos = car->targetPos;
                car->progress = 0;
                animTimer->stop();
                animTimer->deleteLater();
                onFinish(car);
            }
        });
        animTimer->start(16);
    }
};

//Symulacja powrotu
class ReturningState : public AnimationState {
    Location baseLoc;
public:
    ReturningState(Location base)
        : AnimationState(QRandomGenerator::global()->bounded(1000, 3000)), baseLoc(base) {}
        
    void handle(Car* car) override {
        car->targetPos = baseLoc;
        AnimationState::handle(car);
    }
    void onFinish(Car* car) override {
        car->setState(std::make_shared<FreeState>());
    }
    QString name() const override { return "POWROT"; }
};

//Symulacja działań gaśniczych
class ActionState : public CarState {
    Location baseLoc;
public:
    ActionState(Location base) : baseLoc(base) {}
    void handle(Car* car) override {
        int time = QRandomGenerator::global()->bounded(5000, 25000);
        QTimer::singleShot(time, car, [car, this]() {
            car->setState(std::make_shared<ReturningState>(baseLoc));
        });
    }
    QString name() const override { return "AKCJA"; }
};

//Symulacja dojazdu 0-3s
class TravelingState : public AnimationState {
    bool falseAlarm;
    Location baseLoc;
public:
    TravelingState(bool isFalse, Location base)
        : AnimationState(QRandomGenerator::global()->bounded(1000, 3000)), falseAlarm(isFalse), baseLoc(base) {}

    void onFinish(Car* car) override {
        if (falseAlarm) {
            car->setState(std::make_shared<ReturningState>(baseLoc));
        } else {
            car->setState(std::make_shared<ActionState>(baseLoc));
        }
    }
    QString name() const override { return "DOJAZD"; }
};

//Implementacja metod klasy Car
Car::Car(int id, int unitId, Location startLoc) 
    : id(id), parentUnitId(unitId), currentPos(startLoc), progress(0) {
    state = std::make_shared<FreeState>();
}

void Car::setState(std::shared_ptr<CarState> newState) {
    state = newState;
    emit stateChanged(id, state->name());
    state->handle(this);
}

bool Car::isFree() const {
    return state->isFree();
}

void Car::dispatch(Location target, bool falseAlarm) {
    if (isFree()) {
        Location home = currentPos;
        targetPos = target;
        setState(std::make_shared<TravelingState>(falseAlarm, home));
    }
}