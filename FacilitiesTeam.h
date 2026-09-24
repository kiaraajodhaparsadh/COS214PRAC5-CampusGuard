#pragma once
#include "ResponseComponent.h"
#include <string>
#include <map>

// fwd declaration for the Memento
class ComponentStateMemento;

class FacilitiesTeam : public ResponseComponent
{
private:
    int availableMaintenanceCrews;
    // locations where utilities (gas/power) have been shut off
    std::map<std::string, bool> isolatedUtilities;

public:
    FacilitiesTeam(ResponseCoordinator *mediator, std::string id);
    ~FacilitiesTeam() override = default;

    // Core component actions
    void dispatch(std::string location) override;
    void isolateUtilities(std::string location);
    void displayStatus() override;

    // Memento (Undo) actions
    ComponentStateMemento *createMemento() override;
    void restore(ComponentStateMemento *memento) override;
};