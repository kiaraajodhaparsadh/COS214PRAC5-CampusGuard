#include "EvacuateZoneCommand.h"

EvacuateZoneCommand::EvacuateZoneCommand(AccessControlService *receiver, std::string zone)
    : receiver(receiver), targetZone(zone), previousState(nullptr) {}

EvacuateZoneCommand::~EvacuateZoneCommand()
{
    delete previousState;
}

void EvacuateZoneCommand::execute()
{
    previousState = receiver->createMemento();
    receiver->unlockDoors(targetZone);
}

void EvacuateZoneCommand::undo()
{
    if (previousState)
    {
        receiver->restore(previousState);
    }
}