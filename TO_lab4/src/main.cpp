#include <QApplication>
#include <QTimer>
#include "../include/SKKM.h"
#include "../include/MapWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SKKM skkm;
    MapWidget w(&skkm);
    w.setWindowTitle("Symulator SKKM Kraków");
    w.show();

    //Generator zdarzeń
    QTimer generator;
    QObject::connect(&generator, &QTimer::timeout, [&skkm](){
        skkm.createEvent();
    });

    generator.start(4000);
    skkm.createEvent();

    return a.exec();
}