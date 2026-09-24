#include "DispatchSecurity.h"
#include "SecurityTeam.h"
#include "ComponentStateMemento.h"

DispatchSecurity::DispatchSecurity(SecurityTeam *receiver, std::string location)
    : receiver(receiver), location(location), previousState(nullptr) {}

DispatchSecurity::~DispatchSecurity()
{
    delete previousState;
}

void DispatchSecurity::execute()
{
    previousState = receiver->createMemento();
    receiver->dispatch(location);
}

void DispatchSecurity::undo()
{
    if (previousState != nullptr)
    {
        receiver->restore(previousState);
    }
}