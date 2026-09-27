#include "EmergencyLockdown.h"
#include "ComponentStateMemento.h"

EmergencyLockdown::EmergencyLockdown(AccessControlService *receiver)
    : receiver(receiver), previousState(nullptr) {}

EmergencyLockdown::~EmergencyLockdown()
{
    delete previousState;
}

void EmergencyLockdown::execute()
{
    previousState = receiver->createMemento();
    receiver->lockdownDoors();
}

void EmergencyLockdown::undo()
{
    if (previousState != nullptr)
    {
        receiver->restore(previousState);
    }
}