#pragma once
#include "ResponseAction.h"
#include "AccessControlService.h"
#include "ComponentStateMemento.h"
#include <string>

class EvacuateZoneCommand : public ResponseAction
{
private:
    AccessControlService *receiver;
    std::string targetZone;
    ComponentStateMemento *previousState;

public:
    EvacuateZoneCommand(AccessControlService *receiver, std::string zone);
    ~EvacuateZoneCommand() override;

    void execute() override;
    void undo() override;
};