#include "EmergencyOperationsDesk.h"
#include "SecurityTeam.h"            // Concrete Colleague/Receiver
#include "AccessControlService.h"    // Concrete Colleague/Receiver
#include "FacilitiesTeam.h"          // Concrete Colleague/Receiver
#include "CommunicationService.h"    // Concrete Colleague/Receiver
#include "Incident.h"                // State context
#include "MunicipalServiceAdapter.h" // Concrete Adapter
#include "DispatchSecurity.h"        // Concrete Command
#include "LockADoor.h"               // Concrete Command
#include "BroadcastAlert.h"          // Concrete Command
#include <iostream>

EmergencyOperationsDesk::EmergencyOperationsDesk()
{
    // 1. Initialize the Mediator and Invoker
    mediator = new CampusControlRoom();
    console = new OperatorConsole();

    // 2. Initialize the Receivers, linking each to the Mediator
    securityTeam = new SecurityTeam(mediator, "Sec-Alpha", false, "");
    accessControl = new AccessControlService(mediator, "Campus-Gates");
    facilitiesTeam = new FacilitiesTeam(mediator, "Facilities-1");
    comms = new CommunicationService(mediator, "Comms-1");

    // 3. Register every colleague with the mediator. Without this step the
    //    mediator's registered pointers stay null, so its pointer-identity
    //    checks in notify() never match any real sender and coordination
    //    silently does nothing - this registration was missing before, and
    //    it's the reason the facade's dispatches never actually coordinated
    //    anything.
    mediator->registerSecurity(securityTeam);
    mediator->registerAccessControl(accessControl);
    mediator->registerFacilities(facilitiesTeam);
    mediator->registerComms(comms);

    // 4. Create the incident this desk is coordinating and register it too,
    //    so the mediator can gate/advance its lifecycle as colleagues act.
    incident = new Incident("INC-FACADE-1", "FIRE", 4, "");
    mediator->registerIncident(incident);

    // 5. Initialize the Adapter
    municipalAdapter = new MunicipalServiceAdapter();
}

EmergencyOperationsDesk::~EmergencyOperationsDesk()
{
    // Delete in reverse order of creation to satisfy Valgrind
    delete municipalAdapter;
    delete incident;
    delete comms;
    delete facilitiesTeam;
    delete accessControl;
    delete securityTeam;
    delete console;
    delete mediator;
}

void EmergencyOperationsDesk::triggerCampusLockdown(std::string location)
{
    std::cout << "\n=== FACADE: INITIATING CAMPUS LOCKDOWN AT " << location << " ===\n";

    // Every step goes through the console (Command's invoker), not straight
    // to the receiver, so the whole protocol stays logged and any one step
    // can be cancelled with console->undoLastCommand() afterwards. This is
    // the Facade x Command interaction: the facade orchestrates order, but
    // Command still owns how each individual action is carried out.
    console->executeCommand(new LockADoor(accessControl, location));   // subsystem 1: access control
    console->executeCommand(new DispatchSecurity(securityTeam, location)); // subsystem 2: security
                                                                             // (this dispatch also drives
                                                                             // the Mediator's fan-out and
                                                                             // the Incident's own transition)
    console->executeCommand(new BroadcastAlert(comms, "Lockdown in effect at " + location + ". Please stay clear.")); // subsystem 3: comms

    accessControl->displayStatus();
    securityTeam->displayStatus();
    comms->displayStatus();
}

void EmergencyOperationsDesk::undoLastAction()
{
    console->undoLastCommand();
}

// facade + adapter working together: escalates one incident off-campus through the legacy municipal system
void EmergencyOperationsDesk::escalateOffCampus(std::string incidentId, std::string incidentType, std::string areaName)
{
    // State x Facade x Adapter: don't even call the legacy system if the
    // incident's own lifecycle says escalation isn't legal right now (e.g.
    // it's already Resolved, or nobody has been dispatched yet).
    if (!incident->escalate())
    {
        std::cout << "[EmergencyOperationsDesk] Escalation refused by the incident's current state ("
                  << incident->getStateName() << ") - not contacting the municipal service.\n";
        return;
    }

    std::cout << "[EmergencyOperationsDesk] escalating incident " << incidentId << " off campus\n";
    AssistanceOutcome outcome = municipalAdapter->requestAssistance(incidentId, incidentType, areaName);

    if (outcome == AssistanceOutcome::Accepted)
    {
        std::cout << "[EmergencyOperationsDesk] municipal assistance accepted for " << areaName << "\n";
        console->executeCommand(new DispatchSecurity(securityTeam, areaName));
    }
    else
    {
        std::cout << "[EmergencyOperationsDesk] municipal assistance not available, continuing on-campus response\n";
        console->executeCommand(new LockADoor(accessControl, areaName));
    }
}
