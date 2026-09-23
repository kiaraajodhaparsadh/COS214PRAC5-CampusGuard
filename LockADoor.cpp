#include "LockADoor.h"

LockADoor::LockADoor(FacilitiesControlService *receiver, std::string loc)
    : receiver(receiver), location(loc), previousState(nullptr) {}

LockADoor::~LockADoor()
{
    delete previousState;
}

void LockADoor::execute()
{
    previousState = receiver->createMemento();
    receiver->dispatch(location);
}

void LockADoor::undo()
{
    if (previousState != nullptr)
    {
        receiver->restore(previousState);
    }
}