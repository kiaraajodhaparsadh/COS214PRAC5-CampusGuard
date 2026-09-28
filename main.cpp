// CampusGuard - Task 3: two end-to-end runtime stories.
//
// Story 1 (severe fire, driven through the Facade):
//     Facade, Command, Mediator, State, Memento (undo) and Adapter
//     - all six patterns in one execution flow.
//
// Story 2 (minor gas leak, wired by hand - no Facade):
//     Command, Mediator, State, Memento, with the incident driven through
//     its whole lifecycle. Because it bypasses the Facade it also shows the
//     subsystems remain independently usable.
//
// The two stories use different incidents, different team sizes and
// different locations, and each builds (and destroys) its own objects so
// nothing leaks from one story into the next.

#include "CampusControlRoom.h"
#include "SecurityTeam.h"
#include "MedicTeam.h"
#include "FacilitiesTeam.h"
#include "AccessControlService.h"
#include "CommunicationService.h"
#include "OperatorConsole.h"
#include "DispatchSecurity.h"
#include "DispatchMedic.h"
#include "BroadcastAlert.h"
#include "EmergencyLockdown.h"
#include "IsolateUtilitiesCommand.h"
#include "Incident.h"
#include "EmergencyOperationsDesk.h"
#include <iostream>
#include "EvacuateZoneCommand.h"
#include "EmergencyLockdown.h"

// ---------------------------------------------------------------- helpers
static void banner(const std::string &title)
{
    std::cout << "\n==============================================================\n"
              << title << "\n"
              << "==============================================================\n";
}

static void step(int number, const std::string &text)
{
    std::cout << "\n--- Step " << number << ": " << text << " ---\n";
}

//  story 1
// Severe fire in the Engineering lab. The operations desk (Facade) is the
// only thing the "operator" talks to.
static void runStoryOne()
{
    banner("STORY 1: Severe fire in ENG-LAB-2 (incident INC-FACADE-1, severity 4)\n"
           "Patterns: Facade + Command + Mediator + State + Memento + Adapter");

    EmergencyOperationsDesk desk;

    step(1, "Operator tries to escalate off-campus before anyone has responded.\n"
            "        [State] The incident is still Reported, so the desk refuses\n"
            "        and never contacts the municipal service.");
    desk.escalateOffCampus("INC-FACADE-1", "Fire", "ENG-LAB-2");

    step(2, "Operator triggers a campus lockdown through the Facade.\n"
            "        [Facade] one call, three subsystems (access control, security, comms)\n"
            "        [Command] each step is a command submitted to the operator console\n"
            "        [Mediator] security's dispatch fans out to access control + comms\n"
            "        [State] the first dispatch moves the incident Reported -> Responding");
    desk.triggerCampusLockdown("ENG-LAB-2");

    step(3, "Operator realises the alert wording was wrong and cancels it.\n"
            "        [Command + Memento] the alert's memento restores the comms log");
    desk.undoLastAction();

    step(4, "The fire is beyond campus resources, so the desk escalates again.\n"
            "        [State] the incident is now Responding, so escalation is legal\n"
            "        [Adapter] incident type/area become a legacy ticket + urgency code,\n"
            "        and the legacy status code comes back as an AssistanceOutcome");
    desk.escalateOffCampus("INC-FACADE-1", "Fire", "ENG-LAB-2");

    std::cout << "\nStory 1 complete: the municipal service accepted, the incident stays\n"
                 "Responding while outside help arrives.\n";
}

//  story 2
// Minor gas leak in the Chemistry building. Everything is wired by hand, so
// the operator drives the commands directly and we can walk the incident all
// the way through its lifecycle.
static void runStoryTwo()
{
    banner("STORY 2: Minor gas leak in CHEM-BLDG (incident INC-GAS-02, severity 2)\n"
           "Patterns: Command + Mediator + State + Memento (Facade bypassed on purpose)");

    // The mediator has to exist first: every colleague takes a
    // ResponseCoordinator* when it is constructed.
    CampusControlRoom controlRoom;

    SecurityTeam security(&controlRoom, "Sec-Bravo", false, "");
    MedicTeam medics(&controlRoom, "Medic-2", 3, 2, ""); // 3 medics, triage 2 -> 1 medic per dispatch
    FacilitiesTeam facilities(&controlRoom, "Facilities-2");
    AccessControlService accessControl(&controlRoom, "Chem-Doors");
    CommunicationService comms(&controlRoom, "Comms-2");
    Incident gasLeak("INC-GAS-02", "GAS_LEAK", 2, "CHEM-BLDG");

    controlRoom.registerSecurity(&security);
    controlRoom.registerMedic(&medics);
    controlRoom.registerFacilities(&facilities);
    controlRoom.registerAccessControl(&accessControl);
    controlRoom.registerComms(&comms);
    controlRoom.registerIncident(&gasLeak);

    accessControl.addZone("CHEM-BLDG");

    OperatorConsole console;

    step(1, "Facilities isolates the gas supply.\n"
            "        [Command] IsolateUtilitiesCommand -> FacilitiesTeam\n"
            "        [Mediator] 'UtilitiesIsolated' makes the control room tell comms.\n"
            "        [State] a supporting action - the incident stays Reported");
    console.executeCommand(new IsolateUtilitiesCommand(&facilities, "CHEM-BLDG"));
    std::cout << "Incident state: " << gasLeak.getStateName() << "\n";

    step(2, "Security is dispatched.\n"
            "        [State] Reported -> Responding\n"
            "        [Mediator] control room locks the area and warns the campus");
    console.executeCommand(new DispatchSecurity(&security, "CHEM-BLDG"));
    std::cout << "Incident state: " << gasLeak.getStateName() << "\n";

    step(3, "A student feels dizzy, so medics are dispatched.\n"
            "        [Mediator] the control room notifies comms");
    console.executeCommand(new DispatchMedic(&medics, "CHEM-BLDG", 2));
    medics.displayStatus();

    step(4, "Operator mistakenly broadcasts a campus-wide evacuation, then undoes it.\n"
            "        [Command + Memento] the comms log is rolled back to before the alert");
    console.executeCommand(new BroadcastAlert(&comms, "EVACUATE THE ENTIRE CAMPUS NOW"));
    comms.displayStatus();
    console.undoLastCommand();
    comms.displayStatus();

    step(5, "Building is sealed with a full lockdown while the air clears.\n"
            "        [Mediator] 'LockdownAllDoors' -> incident is marked contained\n"
            "        [State] Responding -> Contained");
    console.executeCommand(new EmergencyLockdown(&accessControl));
    std::cout << "Incident state: " << gasLeak.getStateName() << "\n";

    step(6, "Air quality is safe again, so the incident is resolved.\n"
            "        [State] Contained -> Resolved");
    controlRoom.resolveIncident();
    std::cout << "Incident state: " << gasLeak.getStateName() << "\n";

    step(7, "FAILURE CASE: someone dispatches medics to the already-resolved incident.\n"
            "        [State] the incident refuses, so the control room skips coordination.\n"
            "        [Command + Memento] the medic team had already acted, so the operator\n"
            "        undoes the dispatch to put its medic count back");
    std::cout << "(before)\n";
    medics.displayStatus();
    console.executeCommand(new DispatchMedic(&medics, "CHEM-BLDG", 2));
    std::cout << "(after the refused dispatch)\n";
    medics.displayStatus();
    console.undoLastCommand();
    std::cout << "(after undo)\n";
    medics.displayStatus();

    std::cout << "\nStory 2 complete: Reported -> Responding -> Contained -> Resolved.\n";
}

int main()
{
    runStoryOne();
    runStoryTwo();
    return 0;
}