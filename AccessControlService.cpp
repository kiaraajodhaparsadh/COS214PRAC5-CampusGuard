#include "AccessControlService.h"

AccessControlService::AccessControlService(ResponseCoordinator *mediator, std::string id)
    : ResponseComponent(mediator, id)
{
    // default campus doors is unlocked (false)
    facilityDoors["MainGate"] = false;
    facilityDoors["Library"] = false;
}

void AccessControlService::dispatch(std::string location)
{
    // only locks down one zone
    facilityDoors[location] = true;
    this->status = OperationalStatus::Active;

    if (mediator)
    {
        mediator->notify(this, "SingleDoorLocked");
    }
}

void AccessControlService::lockdownDoors()
{
    // lockdownall doors
    for (auto &door : facilityDoors)
    {
        door.second = true;
    }

    this->status = OperationalStatus::Active;

    if (mediator)
    {
        mediator->notify(this, "LockdownAllDoors");
    }
}

void AccessControlService::addZone(std::string zoneName)
{
    // is zone already in the map
    if (facilityDoors.find(zoneName) == facilityDoors.end())
    {
        facilityDoors[zoneName] = false; // unlocked
        std::cout << "[Facilities] Added new zone to control system: " << zoneName << "\n";
    }
    else
    {
        std::cout << "[Facilities] Zone '" << zoneName << "' already exists in the system.\n";
    }
}

void AccessControlService::displayStatus()
{
    const std::string YELLOW = "\033[33m";
    const std::string RESET = "\033[0m";

    std::string statusStr = (status == OperationalStatus::Active) ? "Active/Lockdown" : "Idle/Normal";

    std::cout << YELLOW << "=== [FACILITIES: " << componentID << "] ===" << RESET << "\n";
    std::cout << YELLOW << " > Status: " << RESET << statusStr << "\n";
    std::cout << YELLOW << " > Door States:\n"
              << RESET;

    for (auto const &pair : facilityDoors)
    {
        std::cout << YELLOW << "   - " << pair.first << ": " << RESET
                  << (pair.second ? "LOCKED" : "Unlocked") << "\n";
    }
    std::cout << YELLOW << "=================================" << RESET << "\n\n";
}

ComponentStateMemento *AccessControlService::createMemento()
{
    return new ComponentStateMemento(this->componentID, this->status, this->facilityDoors);
}

void AccessControlService::restore(ComponentStateMemento *memento)
{
    if (!memento)
    {
        return;
    }

    this->componentID = memento->componentID;
    this->status = memento->status;
    this->facilityDoors = memento->facilityDoors;

    std::cout << "[AccessControlService: " + componentID + " ] Reverted to previous state successfully. The previous state of the doors is restored. \n";
}