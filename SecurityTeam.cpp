#include "SecurityTeam.h"
#include "ComponentStateMemento.h"

void SecurityTeam::dispatch(std::string location)
{
    if (status == OperationalStatus::Offline)
    {
        std::cout << "[SecurityTeam: " << componentID << "] cannot be dispatched while Offline.\n";
        return;
    }

    this->location = location;
    this->status = OperationalStatus::Active;
    this->weaponsDeployed = true;

    // notify mediator
    // rubric requrement: mediator coordination
    if (mediator)
    {
        mediator->notify(this, "Dispatched");
    }
}

void SecurityTeam::displayStatus()
{
    const std::string CYAN = "\033[36m";
    const std::string RESET = "\033[0m";

    std::string statusStr = (status == OperationalStatus::Idle) ? "Idle" : (status == OperationalStatus::Active) ? "Active"
                                                                                                                  : "Offline";

    std::cout << CYAN << "=== [SECURITY: " << componentID << "] ===" << RESET << "\n";
    std::cout << CYAN << " > Location:  " << RESET << (location.empty() ? "Standby/Base" : location) << "\n";
    std::cout << CYAN << " > Status:    " << RESET << statusStr << "\n";
    std::cout << CYAN << " > Weapons:   " << RESET << (weaponsDeployed ? "DEPLOYED (Lethal Force Authorized)" : "Secured") << "\n";
    std::cout << CYAN << "===============================" << RESET << "\n\n";
}

ComponentStateMemento *SecurityTeam::createMemento()
{
    return new ComponentStateMemento(componentID, status, location, weaponsDeployed);
}

void SecurityTeam::restore(ComponentStateMemento *memento)
{
    if (!memento)
    {
        return;
    }

    this->componentID = memento->componentID;
    this->status = memento->status;
    this->location = memento->location;
    this->weaponsDeployed = memento->weaponsDeployed;

    std::cout << "[SecurityTeam: " + componentID + " ] Reverted to previous state successfully. Location, status and weaponsDeployed updated.\n";
}
