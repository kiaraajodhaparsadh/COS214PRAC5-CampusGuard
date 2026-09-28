// client of command and adapter, facade of the mediator + everything else
#ifndef EMERGENCY_OPERATIONS_DESK_H
#define EMERGENCY_OPERATIONS_DESK_H

#include "CampusControlRoom.h" // the concrete mediator
#include "OperatorConsole.h"
#include "ExternalAssistanceService.h" //adapter target interface

class SecurityTeam;
class AccessControlService;
class FacilitiesTeam;
class CommunicationService;
class Incident;

class EmergencyOperationsDesk
{
private:
    // subsystems the facade manages:
    //
    // This is stored as a CampusControlRoom* (the concrete mediator), not the
    // abstract ResponseCoordinator*, on purpose: the facade is the one place
    // in the system responsible for wiring everything together, so it needs
    // to call registerSecurity()/registerAccessControl()/etc, which only
    // exist on the concrete class. Every colleague below still only ever
    // sees the abstract ResponseCoordinator* - this concrete knowledge stays
    // inside the facade.
    CampusControlRoom *mediator;
    OperatorConsole *console; // invoker

    // receivers / concrete colleagues
    SecurityTeam *securityTeam;
    AccessControlService *accessControl;
    FacilitiesTeam *facilitiesTeam;
    CommunicationService *comms;

    // the incident this desk is currently coordinating
    Incident *incident;

    // adapter
    ExternalAssistanceService *municipalAdapter; // target - facade is the client here

public:
    EmergencyOperationsDesk();
    ~EmergencyOperationsDesk();

    // multi-step facade workflow required by the rubric: touches
    // AccessControlService, SecurityTeam and CommunicationService, all
    // through OperatorConsole so every step stays logged and cancellable.
    void triggerCampusLockdown(std::string location);

    // facade + adapter working together: escalates one incident off-campus
    // through the legacy municipal system. Gated by the Incident's own
    // state, so escalating a resolved incident is refused before the
    // adapter is ever called.
    void escalateOffCampus(std::string incidentId, std::string incidentType, std::string areaName);

    // lets whoever is driving the demo undo the most recent facade action
    void undoLastAction();
};

#endif
