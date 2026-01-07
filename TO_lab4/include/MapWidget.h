#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include "SKKM.h"

class MapWidget : public QWidget {
    Q_OBJECT
    SKKM* skkm;

public:
    MapWidget(SKKM* s, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPointF toScreen(Location loc);
};

#endif