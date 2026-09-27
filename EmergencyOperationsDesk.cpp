#include "EmergencyOperationsDesk.h"
#include "CampusControlRoom.h"       // Concrete Mediator
#include "SecurityTeam.h"            // Concrete Colleague/Receiver
#include "AccessControlService.h"    // Concrete Colleague/Receiver
#include "MunicipalServiceAdapter.h" // Concrete Adapter
//#include "SecureArea.h"              // Concrete Command
//#include "DispatchUnit.h"            // Concrete Command
#include <iostream>

EmergencyOperationsDesk::EmergencyOperationsDesk()
{
    // 1. Initialize the Mediator and Invoker
    mediator = new CampusControlRoom();
    console = new OperatorConsole();

    // 2. Initialize the Receivers and link them to the Mediator
    securityTeam = new SecurityTeam(mediator, "Sec-Alpha", 10, false);
    accessControl = new AccessControlService(mediator, "Campus-Gates"); // Assuming you build this

    // 3. Initialize the Adapter
    municipalAdapter = new MunicipalServiceAdapter();
}

EmergencyOperationsDesk::~EmergencyOperationsDesk()
{
    // Delete in reverse order of creation to satisfy Valgrind
    delete municipalAdapter;
    delete accessControl;
    delete securityTeam;
    delete console;
    delete mediator;
}

void EmergencyOperationsDesk::triggerCampusLockdown()
{
    std::cout << "\n=== FACADE: INITIATING CAMPUS LOCKDOWN ===\n";

    //dispatch() locks the zone and notifies the mediator internally
    accessControl->dispatch("AllZones");

    // security team is also a concrete colleague, same mediator notification happens here
    securityTeam->dispatch("MainGate");

    // print each receiver's updated state after dispatch
    accessControl->displayStatus();
    securityTeam->displayStatus();
}

// facade + adapter working together: escalates one incident off-campus through the legacy municipal system
void EmergencyOperationsDesk::escalateOffCampus(std::string incidentId, std::string incidentType, std::string areaName) {
    std::cout << "[EmergencyOperationsDesk] escalating incident " << incidentId << " off campus\n";
    AssistanceOutcome outcome = municipalAdapter->requestAssistance(incidentId, incidentType, areaName);

    if (outcome == AssistanceOutcome::Accepted) {
        std::cout << "[EmergencyOperationsDesk] municipal assistance accepted for " << areaName << "\n";
        securityTeam->dispatch(areaName);
    } else {
        std::cout << "[EmergencyOperationsDesk] municipal assistance not available, continuing on-campus response\n";
        accessControl->dispatch(areaName);
    }

}