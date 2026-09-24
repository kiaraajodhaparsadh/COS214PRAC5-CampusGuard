// Demo driver for the Mediator + State (Incident) work.
// This is scaffolding, not the final Task 3 scenario runner - swap it out
// once EmergencyOperationsDesk (Facade) and the Adapter exist. It's kept
// here so `make` has something to build and so there's a known-good
// Valgrind/GDB target while those other pieces are still being written.
#include "CampusControlRoom.h"
#include "SecurityTeam.h"
#include "MedicTeam.h"
#include "CommunicationService.h"
#include "OperatorConsole.h"
#include "DispatchSecurity.h"
#include "DispatchMedic.h"
#include "BroadcastAlert.h"
#include "LockADoor.h"
#include "EmergencyLockdown.h"
#include "Incident.h"
#include <iostream>

int main()
{
    // Mediator must exist before any colleague, since each colleague takes
    // a ResponseCoordinator* at construction time.
    CampusControlRoom controlRoom;

    SecurityTeam security(&controlRoom, "Sec-Alpha", false, "");
    MedicTeam medics(&controlRoom, "Medic-1", 8, 3, "");
    CommunicationService comms(&controlRoom, "Comms-1");
    Incident fireIncident("INC-001", "FIRE", 4, "ENG-LAB-2");

    // Colleagues (and the active incident) register with the mediator after
    // construction.
    controlRoom.registerSecurity(&security);
    controlRoom.registerMedic(&medics);
    controlRoom.registerComms(&comms);
    controlRoom.registerIncident(&fireIncident);

    OperatorConsole console;

    std::cout << "\n--- Dispatch security: fans out via the Mediator AND advances the Incident (Reported -> Responding) ---\n";
    console.executeCommand(new DispatchSecurity(&security, "ENG-LAB-2"));
    std::cout << "Incident is now: " << fireIncident.getStateName() << "\n\n";

    std::cout << "--- Undo that dispatch (Command + Memento) - note this rolls back SecurityTeam, NOT the incident's lifecycle ---\n";
    console.undoLastCommand();
    security.displayStatus();

    std::cout << "--- Re-dispatch security and medics, then lock down all doors (Responding -> Contained) ---\n";
    console.executeCommand(new DispatchSecurity(&security, "ENG-LAB-2"));
    console.executeCommand(new DispatchMedic(&medics, "ENG-LAB-2", 4));
    std::cout << "Incident is now: " << fireIncident.getStateName() << "\n\n";

    std::cout << "--- Resolve the incident (Contained -> Resolved) ---\n";
    controlRoom.resolveIncident();
    std::cout << "Incident is now: " << fireIncident.getStateName() << "\n\n";

    std::cout << "--- State pattern's failure case: dispatching to an already-resolved incident is refused ---\n";
    console.executeCommand(new DispatchSecurity(&security, "ENG-LAB-2"));

    return 0;
}
