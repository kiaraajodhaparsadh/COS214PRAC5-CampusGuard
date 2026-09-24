#pragma once
#include "ResponseComponent.h"
#include "ResponseCoordinator.h" // needed to call mediator->notify()
#include <iostream>
#include <string>

class MedicTeam : public ResponseComponent
{
private:
    int medicsAvailable;
    int triageLevel; // score between 1 and 5
    std::string location;

public:
    // passes mediator and ID up to the base class, and initializes personnel
    MedicTeam(ResponseCoordinator *mediator, int nrMedics, int triageLevel std::string loc)
        : ResponseComponent(mediator, id), medicsAvailable(nrMedics), triageLevel(triageLevel), location(loc) {}

    ~MedicTeam() override = default;

    // declare these overrides so the class is no longer abstract
    void dispatch(std::string location) override;
    void displayStatus() override;

    bool deployMedics(int medics);

    ComponentStateMemento *createMemento() override;
    void restore(ComponentStateMemento *memento) override;
};
