#include "FacilitiesControlService.h"

FacilitiesControlService::FacilitiesControlService(ResponseCoordinator *mediator, std::string id)
    : ResponseComponent(mediator, id)
{
    // default campus doors is unlocked (false)
    facilityDoors["MainGate"] = false;
    facilityDoors["Library"] = false;
}

void FacilitiesControlService::dispatch(std::string location)
{
    // only locks down one zone
    facilityDoors[location] = true;
    this->status = OperationalStatus::Active;

    if (mediator)
    {
        mediator->notify(this, "SingleDoorLocked");
    }
}

void FacilitiesControlService::lockdownDoors()
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

void FacilitiesControlService::addZone(std::string zoneName)
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

void FacilitiesControlService::displayStatus()
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

ComponentStateMemento *FacilitiesControlService::createMemento()
{
    return new ComponentStateMemento(this->componentID, this->status, this->facilityDoors);
}

void FacilitiesControlService::restore(ComponentStateMemento *memento)
{
    if (!memento)
    {
        return;
    }

    this->componentID = memento->componentID;
    this->status = memento->status;
    this->facilityDoors = memento->facilityDoors;

    std::cout << "[FacilitiesControlService: " + componentID + " ] Reverted to previous state successfully. The previous state of the doors is restored. \n";
}