#pragma once
#include "ResponseComponent.h"
#include "ResponseCoordinator.h" // needed to call mediator->notify()
#include <iostream>
#include <string>

class SecurityTeam : public ResponseComponent
{
private:
    // int guardsAvailable; removed this bc not needed
    bool weaponsDeployed;
    std::string location;

public:
    // passes mediator and ID up to the base class, and initializes personnel
    SecurityTeam(ResponseCoordinator *mediator, std::string id, bool weaponsDeployed, std::string loc)
        : ResponseComponent(mediator, id), weaponsDeployed(weaponsDeployed), location(loc) {}

    ~SecurityTeam() override = default;

    // declare these overrides so the class is no longer abstract
    void dispatch(std::string location) override;
    void displayStatus() override;
    ComponentStateMemento *createMemento() override;
    void restore(ComponentStateMemento *memento) override;
};
