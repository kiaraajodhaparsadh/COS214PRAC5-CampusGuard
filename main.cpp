// Demo driver exercising all six patterns together.
// This is scaffolding for Task 3, not the final two-scenario write-up -
// but every class in the project is now actually reachable from here, so
// it doubles as a real Valgrind/GDB target.
#include "CampusControlRoom.h"
#include "SecurityTeam.h"
#include "MedicTeam.h"
#include "FacilitiesTeam.h"
#include "CommunicationService.h"
#include "OperatorConsole.h"
#include "DispatchSecurity.h"
#include "DispatchMedic.h"
#include "BroadcastAlert.h"
#include "IsolateUtilitiesCommand.h"
#include "Incident.h"
#include "EmergencyOperationsDesk.h"
#include <iostream>

int main()
{
    std::cout << "########## PART 1: manually-wired Mediator + Command + Memento + State ##########\n";

    // Mediator must exist before any colleague, since each colleague takes
    // a ResponseCoordinator* at construction time.
    CampusControlRoom controlRoom;

    SecurityTeam security(&controlRoom, "Sec-Alpha", false, "");
    MedicTeam medics(&controlRoom, "Medic-1", 8, 3, "");
    FacilitiesTeam facilities(&controlRoom, "Facilities-1");
    CommunicationService comms(&controlRoom, "Comms-1");
    Incident fireIncident("INC-001", "FIRE", 4, "ENG-LAB-2");

    controlRoom.registerSecurity(&security);
    controlRoom.registerMedic(&medics);
    controlRoom.registerFacilities(&facilities);
    controlRoom.registerComms(&comms);
    controlRoom.registerIncident(&fireIncident);

    OperatorConsole console;

    std::cout << "\n--- Dispatch security: fans out via the Mediator AND advances the Incident (Reported -> Responding) ---\n";
    console.executeCommand(new DispatchSecurity(&security, "ENG-LAB-2"));
    std::cout << "Incident is now: " << fireIncident.getStateName() << "\n\n";

    std::cout << "--- Undo that dispatch (Command + Memento) - rolls back SecurityTeam, NOT the incident's lifecycle ---\n";
    console.undoLastCommand();
    security.displayStatus();

    std::cout << "--- Re-dispatch security and medics ---\n";
    console.executeCommand(new DispatchSecurity(&security, "ENG-LAB-2"));
    console.executeCommand(new DispatchMedic(&medics, "ENG-LAB-2", 4));
    std::cout << "Incident is now: " << fireIncident.getStateName() << "\n\n";

    std::cout << "--- Isolate utilities at the affected location: FacilitiesTeam's own event reaches the Mediator too ---\n";
    console.executeCommand(new IsolateUtilitiesCommand(&facilities, "ENG-LAB-2"));
    facilities.displayStatus();

    std::cout << "--- Failure case: drain the medic team to exactly 0, then watch it go Offline, then refuse outright ---\n";
    console.executeCommand(new DispatchMedic(&medics, "Library", 4));    // 4 remaining -> 0 remaining
    console.executeCommand(new DispatchMedic(&medics, "Gymnasium", 3));  // 0 available -> goes Offline, this dispatch fails
    console.executeCommand(new DispatchMedic(&medics, "Auditorium", 2)); // already Offline -> refused before even checking medics
    medics.displayStatus();

    std::cout << "--- Failure case: undo everything in history, then once more with nothing left ---\n";
    for (int i = 0; i < 8; i++)
    {
        // OperatorConsole::undoLastCommand() already checks for an empty
        // history and refuses cleanly rather than crashing - calling it more
        // times than there are commands is safe, and the last iteration or
        // two below is guaranteed to actually hit that empty case.
        console.undoLastCommand();
    }

    std::cout << "\n########## PART 2: EmergencyOperationsDesk (Facade) driving everything, including the Adapter ##########\n";

    EmergencyOperationsDesk desk;

    // Facade operation touching 3+ subsystems (AccessControlService,
    // SecurityTeam, CommunicationService), all through Command, all
    // triggering Mediator coordination and the Incident's State transitions.
    desk.triggerCampusLockdown("ENG-LAB-2");

    std::cout << "\n--- Undo the last facade action (BroadcastAlert) via Command + Memento ---\n";
    desk.undoLastAction();

    std::cout << "\n--- Escalate off-campus: Facade + Adapter + State gate together ---\n";
    desk.escalateOffCampus("INC-FACADE-1", "Fire", "ENG-LAB-2");

    return 0;
}
