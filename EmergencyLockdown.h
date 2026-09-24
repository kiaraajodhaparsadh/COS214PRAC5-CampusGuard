// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include "AccessControlService.h"
#include <string>

class ResponseComponent; // recievers

class EmergencyLockdown : public ResponseAction
{

protected:
    AccessControlService *receiver;
    ComponentStateMemento *previousState; // stores the snapshot
public:
    EmergencyLockdown(AccessControlService *receiver);
    ~EmergencyLockdown() override;

    void execute() override;
    void undo() override;
};