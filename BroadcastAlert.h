#pragma once
#include "ResponseAction.h"
#include "CommunicationService.h"
#include <string>

class BroadcastAlert : public ResponseAction
{
protected:
    CommunicationService *receiver;
    std::string customMessage;
    ComponentStateMemento *previousState;

public:
    BroadcastAlert(CommunicationService *receiver, std::string message);
    ~BroadcastAlert() override;

    void execute() override;
    void undo() override;
};