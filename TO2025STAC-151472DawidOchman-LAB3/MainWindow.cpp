#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), immunityMode(false)
{
    //Ustawienie głównego widgetu
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    setWindowTitle("Laboratorium 3: Stan oraz pamiątka");
    resize(1000, 800);

    //Inicjalizacja silnika (Plansza 100x80 metrów)
    engine = new SimulationEngine(100.0, 80.0);
    
    //Timer (25 FPS -> 40ms)
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateLoop);

    //Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    //Panel sterowania
    QGroupBox *controlGroup = new QGroupBox("Sterowanie");
    QHBoxLayout *controlLayout = new QHBoxLayout;
    
    QPushButton *btnStart = new QPushButton("Start");
    QPushButton *btnStop = new QPushButton("Stop");
    QPushButton *btnReset = new QPushButton("Resetuj Populację");
    QCheckBox *chkImmunity = new QCheckBox("Start z odpornością");
    
    QPushButton *btnSave = new QPushButton("Zapisz Stan");
    QPushButton *btnLoad = new QPushButton("Wczytaj Stan");

    controlLayout->addWidget(btnStart);
    controlLayout->addWidget(btnStop);
    controlLayout->addWidget(chkImmunity);
    controlLayout->addWidget(btnReset);
    controlLayout->addStretch(); //Odstęp miedzy zapis/odczyt a reszta przyciskow
    controlLayout->addWidget(btnSave);
    controlLayout->addWidget(btnLoad);
    
    controlGroup->setLayout(controlLayout);
    mainLayout->addWidget(controlGroup);
    
    //Legenda
    QLabel *legend = new QLabel("Legenda: Niebieski-Zdrowy, Czerwony-Objawowy, Żółty-Bezobjawowy, Zielony-Odporny. Okrąg przerywany = Zasięg (2m).");
    legend->setStyleSheet("font-weight: bold; margin: 5px;");
    mainLayout->addWidget(legend);

    //Obszar rysowania
    renderArea = new RenderArea;
    renderArea->setEngine(engine);
    renderArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(renderArea);

    //connecty dla przyciskow
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(btnStop, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::resetSimulation);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::saveState);
    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::loadState);
    connect(chkImmunity, &QCheckBox::toggled, [this](bool checked){
        immunityMode = checked;
    });

    resetSimulation();
}

MainWindow::~MainWindow() {
    delete engine;
}

void MainWindow::startSimulation() {
    timer->start(40); // 40ms = 25fps
}

void MainWindow::stopSimulation() {
    timer->stop();
}

void MainWindow::resetSimulation() {
    stopSimulation();
    engine->setInitialPopulation(100, immunityMode); //Start z 30 osobnikami na planszy
    renderArea->update();
}

void MainWindow::updateLoop() {
    engine->update();
    renderArea->update();
}

//Zapis/Odczyt

void MainWindow::saveState() {
    bool wasRunning = timer->isActive();
    timer->stop();

    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz Stan Symulacji", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) {
        if (wasRunning) timer->start();
        return;
    }

    SimulationMemento memento = engine->createMemento();
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(memento.getState().toJson());
        file.close();
        QMessageBox::information(this, "Sukces", "Stan zapisany poprawnie.");
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się zapisać pliku.");
    }
    
    if (wasRunning) timer->start();
}

void MainWindow::loadState() {
    bool wasRunning = timer->isActive();
    timer->stop();

    QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj Stan Symulacji", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) {
        if (wasRunning) timer->start();
        return;
    }

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull()) {
            SimulationMemento memento(doc);
            engine->restoreMemento(memento);
            renderArea->update();
            QMessageBox::information(this, "Sukces", "Stan wczytany.");
        } else {
            QMessageBox::warning(this, "Błąd", "Niepoprawny format pliku.");
        }
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się otworzyć pliku.");
    }
}