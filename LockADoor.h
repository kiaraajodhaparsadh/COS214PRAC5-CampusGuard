// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include "AccessControlService.h"
#include <string>

class ResponseComponent; // recievers

class LockADoor : public ResponseAction
{

protected:
    AccessControlService *receiver;
    std::string location;
    ComponentStateMemento *previousState;

public:
    LockADoor(AccessControlService *receiver, std::string loc);
    ~LockADoor() override;

    void execute() override;
    void undo() override;
};