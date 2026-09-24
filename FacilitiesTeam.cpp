#include "FacilitiesTeam.h"
#include "ComponentStateMemento.h"
#include "ResponseCoordinator.h" // Uncomment if you are using mediator->notify()
#include <iostream>

FacilitiesTeam::FacilitiesTeam(ResponseCoordinator *mediator, std::string id)
    : ResponseComponent(mediator, id), availableMaintenanceCrews(5) {}

void FacilitiesTeam::dispatch(std::string location)
{
    // dispatches 1 crew
    if (availableMaintenanceCrews > 0)
    {
        availableMaintenanceCrews--;
        std::cout << "[FacilitiesTeam] Crew dispatched to " << location
                  << ". Crews remaining: " << availableMaintenanceCrews << "\n";
        this->status = OperationalStatus::Active;
    }
    else
    {
        std::cout << "[FacilitiesTeam] Error: No maintenance crews available!\n";
        this->status = OperationalStatus::Offline;
    }
}

void FacilitiesTeam::isolateUtilities(std::string location)
{
    isolatedUtilities[location] = true;
    std::cout << "[FacilitiesTeam] Physical utilities (gas/power) shut off at " << location << ".\n";
    this->status = OperationalStatus::Active;

    if (mediator)
    {
        // example of triggering the mediator if needed:
        mediator->notify(this, "UtilitiesIsolated");
    }
}

void FacilitiesTeam::displayStatus()
{
    std::cout << "=== [FACILITIES TEAM: " << componentID << "] ===\n";
    std::cout << " > Crews Available: " << availableMaintenanceCrews << "\n";
    for (const auto &pair : isolatedUtilities)
    {
        std::cout << " > " << pair.first << " Utilities: "
                  << (pair.second ? "OFFLINE" : "Online") << "\n";
    }
}

ComponentStateMemento *FacilitiesTeam::createMemento()
{

    return new ComponentStateMemento(this->componentID, this->status,
                                     this->availableMaintenanceCrews, this->isolatedUtilities);
}

void FacilitiesTeam::restore(ComponentStateMemento *memento)
{
    if (!memento)
        return;

    //  FacilitiesTeam is a it, it can directly read the private fields of the memento
    this->componentID = memento->componentID;
    this->status = memento->status;
    this->availableMaintenanceCrews = memento->availableCrews;
    this->isolatedUtilities = memento->utilStates;

    std::cout << "[FacilitiesTeam] State reverted to snapshot successfully. Status, availableMaintenanceCrews and utilities updated.\n";
}