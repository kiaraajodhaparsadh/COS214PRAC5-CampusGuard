#include "IsolateUtilitiesCommand.h"

IsolateUtilitiesCommand::IsolateUtilitiesCommand(FacilitiesTeam *receiver, std::string location)
    : receiver(receiver), targetLocation(location), previousState(nullptr) {}

IsolateUtilitiesCommand::~IsolateUtilitiesCommand()
{
    delete previousState;
}

void IsolateUtilitiesCommand::execute()
{
    previousState = receiver->createMemento();
    receiver->dispatch(targetLocation);
    receiver->isolateUtilities(targetLocation);
}

void IsolateUtilitiesCommand::undo()
{
    if (previousState)
    {
        receiver->restore(previousState);
    }
}