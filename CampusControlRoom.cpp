#include "CampusControlRoom.h"
#include "SecurityTeam.h"
#include "MedicTeam.h"
#include "FacilitiesControlService.h"
#include "CommunicationService.h"
#include <iostream>

CampusControlRoom::CampusControlRoom()
    : securityTeam(nullptr), medicTeam(nullptr), facilities(nullptr), comms(nullptr) {}

void CampusControlRoom::registerSecurity(SecurityTeam *team) { securityTeam = team; }
void CampusControlRoom::registerMedic(MedicTeam *team) { medicTeam = team; }
void CampusControlRoom::registerFacilities(FacilitiesControlService *service) { facilities = service; }
void CampusControlRoom::registerComms(CommunicationService *service) { comms = service; }

void CampusControlRoom::notify(ResponseComponent *sender, std::string event)
{
    // Identity is checked by pointer against the control room's own registered
    // colleagues, not by dynamic_cast on sender - the mediator already knows
    // exactly who each of its colleagues is, so there's no need to ask RTTI.

    if (sender == securityTeam && event == "Dispatched")
    {
        std::cout << "[CampusControlRoom] Security dispatched -> coordinating facilities and comms.\n";

        if (facilities)
        {
            facilities->dispatch(securityTeam->getLocation());
        }
        if (comms)
        {
            comms->broadcastMessage("Security is responding near " + securityTeam->getLocation() +
                                     ". Please avoid the area.");
        }
    }
    else if (sender == medicTeam && event == "Dispatched")
    {
        std::cout << "[CampusControlRoom] Medical team dispatched -> notifying campus.\n";

        if (comms)
        {
            comms->broadcastMessage("Medical response en route to " + medicTeam->getLocation() + ".");
        }
    }
    else if (sender == facilities && event == "LockdownAllDoors")
    {
        std::cout << "[CampusControlRoom] Full lockdown triggered -> notifying campus.\n";

        if (comms)
        {
            comms->broadcastMessage("Campus is in full lockdown. Remain where you are.");
        }
    }
    else if (sender == facilities && event == "SingleDoorLocked")
    {
        // A localised lock doesn't need a campus-wide announcement - this is
        // a deliberate case of an event that does NOT fan out, worth being
        // able to explain in the demo.
        std::cout << "[CampusControlRoom] Noted: a single access point was secured.\n";
    }
    else if (sender == comms && event == "MessageBroadcasted")
    {
        // Logged only. Cascading comms's own event back into another
        // broadcast would create an infinite notify loop.
        std::cout << "[CampusControlRoom] Broadcast logged.\n";
    }
    else
    {
        std::cout << "[CampusControlRoom] Unhandled event '" << event << "' from an unrecognised component.\n";
    }
}
