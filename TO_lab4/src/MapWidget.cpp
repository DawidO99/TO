#include "MapWidget.h"
#include <QPainter>

MapWidget::MapWidget(SKKM* s, QWidget *parent) : QWidget(parent), skkm(s) {
    setMinimumSize(800, 600);
    setStyleSheet("background-color: #2b2b2b;");

    connect(skkm, &SKKM::eventAdded, this, qOverload<>(&QWidget::update));
    connect(skkm, &SKKM::eventRemoved, this, qOverload<>(&QWidget::update));
    
    for(Unit* u : skkm->units) {
        for(Car* c : u->cars) {
            connect(c, &Car::positionChanged, this, qOverload<>(&QWidget::update));
        }
    }
}

QPointF MapWidget::toScreen(Location loc) {
    double w = width();
    double h = height();
    
    double x = (loc.lon - MAP_MIN_LON) / (MAP_MAX_LON - MAP_MIN_LON) * w;
    double y = h - ((loc.lat - MAP_MIN_LAT) / (MAP_MAX_LAT - MAP_MIN_LAT) * h);
    
    return QPointF(x, y);
}

void MapWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    //1. Rysuj Jednostki
    p.setBrush(Qt::cyan);
    p.setPen(Qt::white);
    for(Unit* u : skkm->units) {
        QPointF pos = toScreen(u->location);
        p.drawRect(pos.x()-5, pos.y()-5, 10, 10);
        p.drawText(pos.x()+8, pos.y()+5, u->name);
    }

    //2. Rysuj Zdarzenia
    for(const Event& e : skkm->activeEvents) {
        QPointF pos = toScreen(e.location);
        if (e.type == PZ) p.setBrush(Qt::red);
        else p.setBrush(Qt::yellow);
        
        p.drawEllipse(pos, 8, 8);
        p.drawText(pos.x()+10, pos.y(), e.type == PZ ? "POZAR" : "MZ");
    }

    //3. Rysuj Samochody
    for(Unit* u : skkm->units) {
        for(Car* c : u->cars) {
            if (!c->isFree()) {
                QPointF start = toScreen(c->currentPos);
                QPointF end = toScreen(c->targetPos);
                
                // Interpolacja
                double curX = start.x() + (end.x() - start.x()) * c->progress;
                double curY = start.y() + (end.y() - start.y()) * c->progress;
                
                if(c->state->name() == "DOJAZD") p.setBrush(Qt::green);
                else if(c->state->name() == "POWROT") p.setBrush(Qt::blue);
                else if(c->state->name() == "AKCJA") p.setBrush(Qt::magenta);
                
                p.setPen(Qt::NoPen);
                p.drawEllipse(QPointF(curX, curY), 4, 4);
            }
        }
    }
    
    p.setPen(Qt::white);
    p.drawText(10, 20, "Legenda: Czerwone = Pożar, Żółte = Miejscowe Zagrożenie, Zielone = Dojazd, Niebieskie = Powrót");
}