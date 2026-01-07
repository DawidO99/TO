#ifndef STRATEGIES_H
#define STRATEGIES_H

//Interfejs wzorca Strategia
class IDispatchStrategy {
public:
    virtual int getRequiredCars() = 0;
    virtual ~IDispatchStrategy() = default;
};

//Strategia Pożarowa (PZ)
class FireStrategy : public IDispatchStrategy {
public:
    int getRequiredCars() override { return 3; }
};

//Strategia Miejscowego Zagrożenia (MZ)
class LocalThreatStrategy : public IDispatchStrategy {
public:
    int getRequiredCars() override { return 2; }
};

#endif