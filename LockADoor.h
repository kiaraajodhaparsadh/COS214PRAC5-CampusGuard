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

public:
    LockADoor(FacilitiesControlService *receiver, std::string loc)
        : receiver(receiver), location(loc) {}

    void execute() override
    {
        receiver->dispatch(location); // call a specific method
    }
};