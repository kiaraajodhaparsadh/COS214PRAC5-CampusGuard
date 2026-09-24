#include "MedicTeam.h"
#include "ComponentState.h"
#include "ComponentStateMemento.h"

void MedicTeam::dispatch(std::string location)
{
    if (!state->canDispatch())
    {
        std::cout << this->componentID << " cannot be dispatched while " << getStatusName() << ".\n";
        return;
    }

    if (triageLevel < 3)
    {
        // just deploy one medic
        if (deployMedics(1) == false)
        {
            std::cout << this->componentID << " could not be dispatched. Command failed.\n";
            return;
        }
    }
    else if (triageLevel < 5)
    {
        // 3,4
        if (deployMedics(4) == false)
        {
            std::cout << this->componentID << " could not be dispatched. Command failed.\n";
            return;
        }
    }
    else
    {
        // 5
        if (deployMedics(8) == false)
        {
            std::cout << this->componentID << " could not be dispatched. Command failed.\n";
            return;
        }
    }
    // medics successfully deployed
    this->location = location;
    setState(ActiveState::instance());

    // notify mediator
    // rubric requrement: mediator coordination
    if (mediator)
    {
        mediator->notify(this, "Dispatched");
    }
}

bool MedicTeam::deployMedics(int medics)
{
    if (medicsAvailable == 0)
    {
        std::cout << "NO MORE MEDICS AVAILABLE!! Call reinforcements. " << this->componentID << " is now OFFLINE.\n";

        setState(OfflineState::instance());
        return false;
    }
    else if (medicsAvailable - medics < 0)
    {
        std::cout << "NOT ENOUGH MEDICS AVAILABLE!! Call reinforcements.\n";
        return false;
    }

    medicsAvailable = medicsAvailable - medics;

    return true;
}

void MedicTeam::displayStatus()
{
    const std::string RED = "\033[31m";
    const std::string RESET = "\033[0m";

    std::cout << RED << "=== [MEDICS: " << componentID << "] ===" << RESET << "\n";
    std::cout << RED << " > Location:         " << RESET << (location.empty() ? "Medical Bay" : location) << "\n";
    std::cout << RED << " > Status:           " << RESET << getStatusName() << "\n";
    std::cout << RED << " > Medics Available: " << RESET << medicsAvailable << "\n";
    std::cout << RED << " > Triage Level:     " << RESET << triageLevel << "\n";
    std::cout << RED << "=============================" << RESET << "\n\n";
}
ComponentStateMemento *MedicTeam::createMemento()
{
    return new ComponentStateMemento(componentID, getStatusEnum(), location, medicsAvailable, triageLevel);
}

void MedicTeam::restore(ComponentStateMemento *memento)
{
    if (!memento)
    {
        return;
    }

    this->componentID = memento->componentID;
    setState(ComponentState::fromEnum(memento->status));
    this->location = memento->location;

    this->medicsAvailable = memento->medicsAvailable;
    this->triageLevel = memento->triageLevel;

    std::cout
        << "[MedicTeam: " + componentID + " ] Reverted to previous state successfully. Location, status medics available and triage level updated.\n";
}
