#include "CampusControlRoom.h"
#include "SecurityTeam.h"
#include "MedicTeam.h"
#include "FacilitiesTeam.h"
#include "CommunicationService.h"
#include "Incident.h"
#include <iostream>

CampusControlRoom::CampusControlRoom()
    : securityTeam(nullptr),
      medicTeam(nullptr),
      facilitiesTeam(nullptr),
      comms(nullptr),
      incident(nullptr)
{
}

void CampusControlRoom::registerSecurity(SecurityTeam *team)
{
    securityTeam = team;
}

void CampusControlRoom::registerMedic(MedicTeam *team)
{
    medicTeam = team;
}

void CampusControlRoom::registerFacilities(FacilitiesTeam *team)
{
    facilitiesTeam = team;
}

void CampusControlRoom::registerComms(CommunicationService *service)
{
    comms = service;
}

void CampusControlRoom::registerIncident(Incident *activeIncident)
{
    incident = activeIncident;
}

bool CampusControlRoom::resolveIncident()
{
    if (!incident)
    {
        std::cout << "[CampusControlRoom] No incident registered to resolve.\n";
        return false;
    }

    return incident->resolve();
}

void CampusControlRoom::notify(ResponseComponent *sender, std::string event)
{
    // Identity is checked by pointer against the control room's own
    // registered colleagues. The mediator already knows exactly who
    // each colleague is, so there is no need to use dynamic_cast.

    if (sender == securityTeam && event == "Dispatched")
    {
        // State x Mediator: the incident's own lifecycle gate decides
        // whether this dispatch is allowed to affect the wider system.
        if (incident && !incident->dispatchUnit())
        {
            std::cout << "[CampusControlRoom] Security acted, but the "
                         "incident refused the transition - skipping "
                         "further coordination.\n";
            return;
        }

        std::cout << "[CampusControlRoom] Security dispatched -> "
                     "coordinating facilities and comms.\n";

        if (facilitiesTeam)
        {
            facilitiesTeam->dispatch(securityTeam->getLocation());
        }

        if (comms)
        {
            comms->broadcastMessage(
                "Security is responding near " +
                securityTeam->getLocation() +
                ". Please avoid the area.");
        }
    }
    else if (sender == medicTeam && event == "Dispatched")
    {
        if (incident && !incident->dispatchUnit())
        {
            std::cout << "[CampusControlRoom] Medics acted, but the "
                         "incident refused the transition - skipping "
                         "further coordination.\n";
            return;
        }

        std::cout << "[CampusControlRoom] Medical team dispatched -> "
                     "notifying campus.\n";

        if (comms)
        {
            comms->broadcastMessage(
                "Medical response en route to " +
                medicTeam->getLocation() + ".");
        }
    }
    else if (sender == facilitiesTeam && event == "LockdownAllDoors")
    {
        if (incident && !incident->contain())
        {
            std::cout << "[CampusControlRoom] Lockdown occurred, but "
                         "the incident could not be marked contained.\n";
            return;
        }

        std::cout << "[CampusControlRoom] Full lockdown triggered -> "
                     "notifying campus.\n";

        if (comms)
        {
            comms->broadcastMessage(
                "Campus is in full lockdown. Remain where you are.");
        }
    }
    else if (sender == facilitiesTeam && event == "SingleDoorLocked")
    {
        // A localised lock does not need a campus-wide announcement,
        // and it does not move the incident lifecycle forward.
        std::cout << "[CampusControlRoom] Noted: a single access "
                     "point was secured.\n";
    }
    else if (sender == comms && event == "MessageBroadcasted")
    {
        // Logged only. Cascading communication events back into
        // another broadcast would create an infinite notify loop.
        std::cout << "[CampusControlRoom] Broadcast logged.\n";
    }
    else
    {
        std::cout << "[CampusControlRoom] Unhandled event '"
                  << event
                  << "' from an unrecognised component.\n";
    }
}