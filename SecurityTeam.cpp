#include "SecurityTeam.h"
#include "ComponentState.h"
#include "ComponentStateMemento.h"

void SecurityTeam::dispatch(std::string location)
{
    if (!state->canDispatch())
    {
        std::cout << "[SecurityTeam: " << componentID << "] cannot be dispatched while " << getStatusName() << ".\n";
        return;
    }

    this->location = location;
    setState(ActiveState::instance());
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

    std::cout << CYAN << "=== [SECURITY: " << componentID << "] ===" << RESET << "\n";
    std::cout << CYAN << " > Location:  " << RESET << (location.empty() ? "Standby/Base" : location) << "\n";
    std::cout << CYAN << " > Status:    " << RESET << getStatusName() << "\n";
    std::cout << CYAN << " > Weapons:   " << RESET << (weaponsDeployed ? "DEPLOYED (Lethal Force Authorized)" : "Secured") << "\n";
    std::cout << CYAN << "===============================" << RESET << "\n\n";
}

ComponentStateMemento *SecurityTeam::createMemento()
{
    return new ComponentStateMemento(componentID, getStatusEnum(), location, weaponsDeployed);
}

void SecurityTeam::restore(ComponentStateMemento *memento)
{
    if (!memento)
    {
        return;
    }

    this->componentID = memento->componentID;
    setState(ComponentState::fromEnum(memento->status));

    this->location = memento->location;
    this->weaponsDeployed = memento->weaponsDeployed;

    std::cout << "[SecurityTeam: " + componentID + " ] Reverted to previous state successfully. Location, status and weaponsDeployed updated.\n";
}
