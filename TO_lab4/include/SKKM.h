#ifndef SKKM_H
#define SKKM_H

#include <QObject>
#include <QList>
#include "Unit.h"
#include "Location.h"

class SKKM : public QObject {
    Q_OBJECT
public:
    QList<Unit*> units;
    QList<Event> activeEvents;
    int eventCounter;

    SKKM();
    void createEvent();

    signals:
        void eventAdded(Event e);
    void eventRemoved(int id);
};

#endif