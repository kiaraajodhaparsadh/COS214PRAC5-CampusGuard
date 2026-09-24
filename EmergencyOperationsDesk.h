// client of command and adapter, facade of the facade
#pragma once
#include "ResponseCoordinator.h"
#include "OperatorConsole.h"
#include "ResponseComponent.h"
#include "ExternalAssistanceService.h" //adapter target interface

class EmergencyOperationsDesk
{
private:
    // subsystems the facade manages:
    ResponseCoordinator *mediator; // mediator
    OperatorConsole *console;      // invoker

    // receivers/ concrete collegues
    ResponseComponent *securityTeam;
    ResponseComponent *accessControl;

    // adapter
    ExternalAssistanceService *municipalAdapter;

public:
    EmergencyOperationsDesk();
    ~EmergencyOperationsDesk();

    // multi-step facade workflow required by the rubric:
    void triggerCampusLockdown();
};