#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include "SimulationCore.h"

//Widget rysujący pole symulacji
class RenderArea : public QWidget {
    Q_OBJECT
    SimulationEngine* engine;

public:
    RenderArea(QWidget* parent = nullptr) : QWidget(parent), engine(nullptr) {
        setBackgroundRole(QPalette::Base);
        setAutoFillBackground(true);
    }

    void setEngine(SimulationEngine* e) { engine = e; }

protected:
    void paintEvent(QPaintEvent*) override {
        if (!engine) return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        //Rysowanie ramki
        painter.setPen(Qt::black);
        painter.drawRect(0, 0, width() - 1, height() - 1);

        //Skalowanie metrów na piksele
        double scaleX = width() / engine->getWidth();
        double scaleY = height() / engine->getHeight();

        const std::vector<Agent>& agents = engine->getAgents();

        for (const auto& agent : agents) {
            QColor color;
            //Kolorowanie osobnikow wg stanu
            switch (agent.health) {
                case HealthStatus::Susceptible:
                    color = Qt::blue; break;
                case HealthStatus::Resistant:
                    color = Qt::green; break;
                case HealthStatus::Infected:
                    if (agent.symptoms == SymptomStatus::Symptomatic)
                        color = Qt::red;
                    else
                        color = Qt::darkYellow;
                    break;
            }

            painter.setBrush(color);
            painter.setPen(Qt::black);

            //rysowanie osobnika
            double px = agent.position.getX() * scaleX;
            double py = agent.position.getY() * scaleY;
            double r = 4.0; // promień wizualny
            painter.drawEllipse(QPointF(px, py), r, r);

            //Jesli chory - obszar zakazania (2m)
            if (agent.health == HealthStatus::Infected) {
                 painter.setBrush(Qt::NoBrush);
                 painter.setPen(QPen(Qt::red, 1, Qt::DotLine));
                 double radiusPx = 2.0 * scaleX; //2 metry w skali
                 painter.drawEllipse(QPointF(px, py), radiusPx, radiusPx);
            }
        }
    }
};

// Główne okno aplikacji
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSimulation();
    void stopSimulation();
    void saveState();
    void loadState();
    void updateLoop();
    void resetSimulation();

private:
    SimulationEngine* engine;
    RenderArea* renderArea;
    QTimer* timer;
    bool immunityMode; //Czy startujemy z odpornością
};

#endif // MAINWINDOW_H