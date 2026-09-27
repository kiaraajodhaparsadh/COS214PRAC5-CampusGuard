// client of command and adapter, facade of the facade
#ifndef EMERGENCY_OPERATIONS_DESK_H
#define EMERGENCY_OPERATIONS_DESK_H

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
    ExternalAssistanceService *municipalAdapter; //target - facade is the client here

public:
    EmergencyOperationsDesk();
    ~EmergencyOperationsDesk();

    // multi-step facade workflow required by the rubric:
    void triggerCampusLockdown();

    //facade + adapter working together
    void escalateOffCampus(std::string incidentId, std::string incidentType, std::string areaName);
};

#endif