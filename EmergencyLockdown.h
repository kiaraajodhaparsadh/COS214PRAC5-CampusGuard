// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include "FacilitiesControlService.h"
#include <string>

class ResponseComponent; // recievers

class EmergencyLockdown : public ResponseAction
{

protected:
    FacilitiesControlService *receiver;   // Point directly to MedicTeam instead of the base
    ComponentStateMemento *previousState; // stores the snapshot
public:
    EmergencyLockdown(FacilitiesControlService *receiver);
    ~EmergencyLockdown() override;

    void execute() override;
    void undo() override;
};