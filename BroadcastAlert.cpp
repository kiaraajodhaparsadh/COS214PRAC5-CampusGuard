#include "BroadcastAlert.h"
#include "ComponentStateMemento.h"

BroadcastAlert::BroadcastAlert(CommunicationService *receiver, std::string message)
    : receiver(receiver), customMessage(message), previousState(nullptr) {}

BroadcastAlert::~BroadcastAlert()
{
    delete previousState;
}

void BroadcastAlert::execute()
{
    previousState = receiver->createMemento();
    receiver->broadcastMessage(customMessage);
}

void BroadcastAlert::undo()
{
    if (previousState != nullptr)
    {
        receiver->restore(previousState);
    }
}