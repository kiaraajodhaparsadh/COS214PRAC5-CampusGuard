// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include "FacilitiesControlService.h"
#include <string>

class ResponseComponent; // recievers

class EmergencyLockdown : public ResponseAction
{

protected:
    FacilitiesControlService *receiver; // Point directly to MedicTeam instead of the base

public:
    EmergencyLockdown(FacilitiesControlService *receiver)
        : receiver(receiver) {}

    void execute() override
    {
        receiver->lockdownDoors(); // call a specific method
    }
};