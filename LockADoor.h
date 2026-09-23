// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include "FacilitiesControlService.h"
#include <string>

class ResponseComponent; // recievers

class LockADoor : public ResponseAction
{

protected:
    FacilitiesControlService *receiver;
    std::string location;
    ComponentStateMemento *previousState;

public:
    LockADoor(FacilitiesControlService *receiver, std::string loc);
    ~LockADoor() override;

    void execute() override;
    void undo() override;
};