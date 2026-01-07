#ifndef SIMULATIONCORE_H
#define SIMULATIONCORE_H

#include "Vector2D.h"
#include <vector>
#include <map>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QRandomGenerator>

//klasy odpowiedzialne za stan
enum class HealthStatus {
    Susceptible, //Wrażliwy, ale zdrowy
    Infected,    //Zakażony
    Resistant    //Odporny i zdrowy
};

enum class SymptomStatus {
    None,           //Brak (dla zdrowych)
    Asymptomatic,   //Bezobjawowy
    Symptomatic     //Objawowy
};

//Agent - pojedynczy osobnik
class Agent {
public:
    Vector2D position;
    Vector2D velocity;

    HealthStatus health;
    SymptomStatus symptoms;

    // Liczniki czasu w sekundach
    double timeInfected;      //Jak długo jest zakażony
    double infectionDuration; //Ile ma trwać zakażenie (20-30s)

    std::map<int, double> exposureTimers; //mapa przechowująca jak długo osobnik stoi obok danego innego osobnika

    int id; //id osobnika, do sledzenia kontaktu miedzy osobnikami

    Agent(int _id, Vector2D pos, Vector2D vel, bool resistant = false);

    // Metody do serializacji (Memento)
    QJsonObject toJson() const;
    static Agent fromJson(const QJsonObject& json);
};

//Wzorzec Memento (Pamiątka) - Klasa przechowująca stan całej symulacji
class SimulationMemento {
private:
    QJsonDocument state;

public:
    SimulationMemento(const QJsonDocument& stateDoc) : state(stateDoc) {}
    QJsonDocument getState() const { return state; }
};

//Silnik Symulacji (Originator w wzorcu Memento)
class SimulationEngine {
private:
    std::vector<Agent> agents; //wektor osobnikow
    double width;
    double height;
    int nextId;

    // Parametry symulacji
    const double TIME_STEP = 0.04; // 1 sekunda / 25 kroków = 0.04s
    const double MAX_SPEED = 2.5;  // m/s
    const double INFECT_RADIUS = 2.0; // metry
    const double EXPOSURE_THRESHOLD = 3.0; // sekundy wymagane do zakażenia

public:
    SimulationEngine(double w, double h);

    void update(); // Jeden krok symulacji (fizyka + logika wirusa)
    void spawnAgent(bool forceInfected = false, bool forceResistant = false); //nowy osobnik na planszy

    // Gettery do wizualizacji
    const std::vector<Agent>& getAgents() const { return agents; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }

    // Zarządzanie Pamiątkami (Save/Load)
    SimulationMemento createMemento() const;
    void restoreMemento(const SimulationMemento& memento);

    void clearAgents() { agents.clear(); nextId = 0; }
    void setInitialPopulation(int count, bool withImmunity);

private:
    void handleBoundaries(Agent& agent); //granica planszy
    void handleInfectionLogic(); //logika zarazania
    void updateMovement(Agent& agent); //zmiany szybkosci i kierunku
};

#endif // SIMULATIONCORE_H