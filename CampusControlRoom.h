#pragma once
#include "ResponseCoordinator.h"

// forward declarations only - CampusControlRoom.cpp includes the real headers
class SecurityTeam;
class MedicTeam;
class FacilitiesControlService;
class CommunicationService;

// CONCRETE MEDIATOR PARTICIPANT
//
// CampusControlRoom does NOT own any colleague (aggregation, not composition):
// components are created independently by whoever wires the system up (e.g.
// EmergencyOperationsDesk), and are registered here afterwards. That ordering
// exists because a ResponseComponent needs a ResponseCoordinator* at
// construction time, so the control room has to exist first, before any
// colleague can be built and handed a pointer to it.
class CampusControlRoom : public ResponseCoordinator
{
private:
    SecurityTeam *securityTeam;
    MedicTeam *medicTeam;
    FacilitiesControlService *facilities;
    CommunicationService *comms;

public:
    CampusControlRoom();
    ~CampusControlRoom() override = default; // no delete here: doesn't own its colleagues

    // registration - call these once, right after constructing each colleague
    void registerSecurity(SecurityTeam *team);
    void registerMedic(MedicTeam *team);
    void registerFacilities(FacilitiesControlService *service);
    void registerComms(CommunicationService *service);

    void notify(ResponseComponent *sender, std::string event) override;
};
