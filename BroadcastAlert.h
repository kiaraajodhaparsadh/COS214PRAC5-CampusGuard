#pragma once
#include "ResponseAction.h"
#include "CommunicationService.h"
#include <string>

class BroadcastAlert : public ResponseAction
{
protected:
    CommunicationService *receiver;
    std::string customMessage;

public:
    BroadcastAlert(CommunicationService *receiver, std::string message)
        : receiver(receiver), customMessage(message) {}

    ~BroadcastAlert() override = default;

    void execute() override
    {
        receiver->broadcastMessage(customMessage);
    }
};