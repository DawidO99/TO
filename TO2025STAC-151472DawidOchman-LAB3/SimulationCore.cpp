#include "SimulationCore.h"
#include <QDebug>

Agent::Agent(int _id, Vector2D pos, Vector2D vel, bool resistant) 
    : id(_id), position(pos), velocity(vel), timeInfected(0.0)
{
    if (resistant) {
        health = HealthStatus::Resistant;
        symptoms = SymptomStatus::None;
    } else {
        health = HealthStatus::Susceptible;
        symptoms = SymptomStatus::None;
    }
    
    // Losowanie czasu trwania choroby (20-30s)
    infectionDuration = 20.0 + QRandomGenerator::global()->generateDouble() * 10.0;
}

QJsonObject Agent::toJson() const {
    QJsonObject json;
    json["id"] = id;
    json["posX"] = position.getX();
    json["posY"] = position.getY();
    json["velX"] = velocity.getX();
    json["velY"] = velocity.getY();
    json["health"] = static_cast<int>(health);
    json["symptoms"] = static_cast<int>(symptoms);
    json["timeInfected"] = timeInfected;
    json["infectionDuration"] = infectionDuration;
    return json;
}

Agent Agent::fromJson(const QJsonObject& json) {
    Vector2D pos(json["posX"].toDouble(), json["posY"].toDouble());
    Vector2D vel(json["velX"].toDouble(), json["velY"].toDouble());
    Agent a(json["id"].toInt(), pos, vel);
    
    a.health = static_cast<HealthStatus>(json["health"].toInt());
    a.symptoms = static_cast<SymptomStatus>(json["symptoms"].toInt());
    a.timeInfected = json["timeInfected"].toDouble();
    a.infectionDuration = json["infectionDuration"].toDouble();
    
    return a;
}

SimulationEngine::SimulationEngine(double w, double h) 
    : width(w), height(h), nextId(0) {}

void SimulationEngine::setInitialPopulation(int count, bool withImmunity) {
    agents.clear();
    for (int i = 0; i < count; ++i) {
        //pozycja na planszy
        double x = QRandomGenerator::global()->generateDouble() * width;
        double y = QRandomGenerator::global()->generateDouble() * height;
        
        // Losowa prędkość max 2.5 oraz z jakim katem sie porusza
        //double speed = MAX_SPEED; //do testow
        double speed = QRandomGenerator::global()->generateDouble() * MAX_SPEED;
        double angle = QRandomGenerator::global()->generateDouble() * 2 * M_PI;
        
        Vector2D vel(std::cos(angle) * speed, std::sin(angle) * speed); //zmieniamy kat i predkosc na wektor

        //jesli zaznaczymy generowanie z odpornoscia to kazdy osobnik ma 20% szans na bycie odpornym
        bool isResistant = false;
        if (withImmunity) {
            isResistant = (QRandomGenerator::global()->generateDouble() < 0.2);
        }
        
        agents.emplace_back(nextId++, Vector2D(x, y), vel, isResistant);
    }
}

void SimulationEngine::spawnAgent(bool forceInfected, bool forceResistant) {
    //Losowe wejście na krawędzi
    double x, y;
    if (QRandomGenerator::global()->bounded(2) == 0) {//lewa/prawa strona planszy (bounded to rzut moneta gdzie wchodzimy)
        x = (QRandomGenerator::global()->bounded(2) == 0) ? 0 : width;
        y = QRandomGenerator::global()->generateDouble() * height;
    } else{  //Góra/Dół planszy
        x = QRandomGenerator::global()->generateDouble() * width;
        y = (QRandomGenerator::global()->bounded(2) == 0) ? 0 : height;
    }

    double speed = QRandomGenerator::global()->generateDouble() * MAX_SPEED;
    //kierujemy wektor prędkości do środka planszy
    Vector2D pos(x, y);
    Vector2D center(width/2, height/2);
    Vector2D dir = (center - pos).normalize();
    Vector2D vel = dir * speed;
    vel = vel.rotate((QRandomGenerator::global()->generateDouble() - 0.5)); //zeby ruch nie był sztywny

    Agent newAgent(nextId++, pos, vel, forceResistant);

    //10% szans na zakażenie przy wejściu
    if (!forceResistant && (forceInfected || QRandomGenerator::global()->generateDouble() < 0.1)) {
        newAgent.health = HealthStatus::Infected;
        //50% szans na objawy
        newAgent.symptoms = (QRandomGenerator::global()->bounded(2) == 0) 
                            ? SymptomStatus::Asymptomatic 
                            : SymptomStatus::Symptomatic;
    }
    
    agents.push_back(newAgent);
}

void SimulationEngine::updateMovement(Agent& agent) {
    //Losowa zmiana kierunku/prędkości
    if (QRandomGenerator::global()->generateDouble() < 0.05) { //5% szansy na zmianę ruchu
        double angleChange = (QRandomGenerator::global()->generateDouble() - 0.5); //+/- 0.5 rad
        agent.velocity = agent.velocity.rotate(angleChange);
        
        double speedChange = (QRandomGenerator::global()->generateDouble() - 0.5); 
        double currentSpeed = agent.velocity.abs();
        double newSpeed = std::max(0.1, std::min(MAX_SPEED, currentSpeed + speedChange));
        agent.velocity = agent.velocity.normalize() * newSpeed;
    }

    agent.position += agent.velocity * TIME_STEP; //S = V * t
}

void SimulationEngine::handleBoundaries(Agent& agent) {
    bool outX = agent.position.getX() < 0 || agent.position.getX() > width;
    bool outY = agent.position.getY() < 0 || agent.position.getY() > height;

    if (outX || outY) {
        //50% szans na powrót, 50% na wyjście
        if (QRandomGenerator::global()->bounded(2) == 0) {
            //Zawróć (odbij)
            if (outX) {
                agent.velocity.setX(-agent.velocity.getX());
                double x = agent.position.getX();
                agent.position.setX(x < 0 ? 0.1 : width - 0.1);
            }
            if (outY) {
                agent.velocity.setY(-agent.velocity.getY());
                double y = agent.position.getY();
                agent.position.setY(y < 0 ? 0.1 : height - 0.1);
            }
        } else {
            //wyjscie z planszy, usuniecie osobnika w update()
            agent.position.setX(-999); //oznaczamy osobnika do usuniecia
        }
    }
}

//source - chory osobnik, target - zagrozony zarazeniem osobnik
void SimulationEngine::handleInfectionLogic() {
    for (auto& target : agents) {
        //Tylko wrażliwi i zdrowi mogą się zarazić
        if (target.health != HealthStatus::Susceptible) continue;

        for (const auto& source : agents) {
            if (target.id == source.id) continue; //odrzucamy sprawdzenie samego ze soba
            if (source.health != HealthStatus::Infected) continue; //jesli source nie jesr zakazony to nie ma czym zarazic, wiec odrzucamy

            double dist = target.position.distanceTo(source.position);

            if (dist <= INFECT_RADIUS) {
                target.exposureTimers[source.id] += TIME_STEP; //dodajemy kolejne kroki (1s = 25 krokow)
                //sprawdzamy czy >=3s kontaktu
                if (target.exposureTimers[source.id] >= EXPOSURE_THRESHOLD) { //>=1 do testow
                    double chance = 0.0; //szanse na zarazenie 50%/100% w zaleznosci od posiadania objawow
                    if (source.symptoms == SymptomStatus::Symptomatic) chance = 1.0;
                    else if (source.symptoms == SymptomStatus::Asymptomatic) chance = 0.5;

                    if (QRandomGenerator::global()->generateDouble() < chance) {
                        target.health = HealthStatus::Infected;
                        target.symptoms = (QRandomGenerator::global()->bounded(2) == 0) 
                                          ? SymptomStatus::Asymptomatic 
                                          : SymptomStatus::Symptomatic;
                        target.exposureTimers.clear(); //reset czasu przy zarazonym
                        break;
                    }
                    else {
                        target.exposureTimers[source.id] = 0; //reset licznika 3s jesli nie zarazony
                    }
                }
            } else {
                target.exposureTimers.erase(source.id); //reset licznika jesli odleglosc >2m
            }
        }
    }
}

//udpate to funkcja odpowiadajaca za 1 krok symulacji, wywolana w petli
void SimulationEngine::update() {
    //Jesli minie czas infekcji (20-30s) to ozdrawiamy
    for (auto& agent : agents) {
        if (agent.health == HealthStatus::Infected) {
            agent.timeInfected += TIME_STEP;
            if (agent.timeInfected >= agent.infectionDuration) {
                agent.health = HealthStatus::Resistant;
                agent.symptoms = SymptomStatus::None;
            }
        }
    }

    //Rozprzestrzenianie wirusa
    handleInfectionLogic();

    //Logika usuwania osobnikow z planszy
    for (auto it = agents.begin(); it != agents.end(); ) {
        updateMovement(*it);
        handleBoundaries(*it);

        //Usuwanie osobnikow ktorzy wyszli poza plansze (oznaczenie przez x = -999)
        if (it->position.getX() == -999) {
            it = agents.erase(it);
        } else {
            ++it;
        }
    }

    //Pojawianie sie nowycbosobnikow
    // Co ~20 kroków (nie co klatkę) próba dodania kogoś, jeśli populacja spadła
    static int stepCounter = 0;
    stepCounter++;
    if (stepCounter % 20 == 0 && agents.size() < 200) { //chcemy max 200 osobnikow na planszy, dodajemy co 20 klatek (<1s), testy : 100,500,1000
        spawnAgent();
    }
}


//save/load
SimulationMemento SimulationEngine::createMemento() const {
    QJsonArray agentsArr;
    for (const auto& a : agents) {
        agentsArr.append(a.toJson());
    }
    
    QJsonObject root;
    root["width"] = width;
    root["height"] = height;
    root["nextId"] = nextId;
    root["agents"] = agentsArr;

    return SimulationMemento(QJsonDocument(root));
}

void SimulationEngine::restoreMemento(const SimulationMemento& memento) {
    QJsonObject root = memento.getState().object();
    
    width = root["width"].toDouble();
    height = root["height"].toDouble();
    nextId = root["nextId"].toInt();
    
    agents.clear();
    QJsonArray agentsArr = root["agents"].toArray();
    for (const auto& val : agentsArr) {
        agents.push_back(Agent::fromJson(val.toObject()));
    }
}