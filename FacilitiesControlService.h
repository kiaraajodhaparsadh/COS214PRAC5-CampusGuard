#pragma once
#include "ResponseComponent.h"
#include "ResponseCoordinator.h" // needed to call mediator->notify()
#include <map>
#include <string>
#include <vector>
#include <iostream>
class FacilitiesControlService : public ResponseComponent
{
private:
    std::map<std::string, bool> facilityDoors; // true=locked

public:
    FacilitiesControlService(ResponseCoordinator *mediator, std::string id);

    ~FacilitiesControlService() override = default;

    // declare these overrides so the class is no longer abstract
    void dispatch(std::string location) override;
    void displayStatus() override;

    ComponentStateMemento *createMemento() override;
    void restore(ComponentStateMemento *memento) override;

    // add a new zone
    void addZone(std::string zoneName);

    void lockdownDoors();
};