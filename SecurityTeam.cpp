#include "SecurityTeam.h"

void SecurityTeam::dispatch(std::string location)
{
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

    std::string statusStr;
    switch (status)
    {
    case OperationalStatus::Idle:
        statusStr = "Idle";
        break;
    case OperationalStatus::Active:
        statusStr = "Active";
        break;
    case OperationalStatus::Offline:
        statusStr = "Offline";
        break;
    }

    std::cout << CYAN << "=== [SECURITY: " << componentID << "] ===" << RESET << "\n";
    std::cout << CYAN << " > Location:  " << RESET << (location.empty() ? "Standby/Base" : location) << "\n";
    std::cout << CYAN << " > Status:    " << RESET << statusStr << "\n";
    std::cout << CYAN << " > Weapons:   " << RESET << (weaponsDeployed ? "DEPLOYED (Lethal Force Authorized)" : "Secured") << "\n";
    std::cout << CYAN << "===============================" << RESET << "\n\n";
}

ComponentStateMemento *SecurityTeam::createMemento()
{
    return nullptr;
}

void SecurityTeam::restore(ComponentStateMemento *memento)
{
}
