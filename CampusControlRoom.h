#include "ResponseCoordinator.h"

// forward declarations only - CampusControlRoom.cpp includes the real headers
class SecurityTeam;
class MedicTeam;
class FacilitiesTeam;
class CommunicationService;
class Incident;

// CONCRETE MEDIATOR PARTICIPANT

// CampusControlRoom does NOT own any colleague, nor the incident (aggregation)
// components and the incident are created independently by
// whoever wires the system up (currently main.cpp/ Facade),
// and are registered here afterwards. That ordering exists because a
// ResponseComponent needs a ResponseCoordinator* at construction time, so the
// control room has to exist first, before any colleague can be built and
// handed a pointer to it.
//
// The control room now does two jobs: coordinate colleagues (as before), and
// drive the registered Incident's lifecycle forward as those colleagues act.
// This is the State x Mediator interaction: an incident's state transitions
// are triggered by the same events the mediator already coordinates on,
// rather than by some separate call path.

class CampusControlRoom : public ResponseCoordinator
{
private:
    SecurityTeam *securityTeam;
    MedicTeam *medicTeam;
    FacilitiesTeam *facilitiesTeam;
    CommunicationService *comms;
    Incident *incident;

public:
    CampusControlRoom();
    ~CampusControlRoom() override = default; // no delete here: doesn't own its colleagues or the incident

    // registration - call these once, right after constructing each colleague
    void registerSecurity(SecurityTeam *team);
    void registerMedic(MedicTeam *team);
    void registerFacilities(FacilitiesTeam *team);
    void registerComms(CommunicationService *service);
    void registerIncident(Incident *activeIncident);

    // exposed for whoever is driving the demo (main.cpp today, the Facade
    // later) to resolve an incident once it's been contained - resolving
    // isn't triggered by any component event, so it needs its own entry point.
    bool resolveIncident();

    void notify(ResponseComponent *sender, std::string event) override;
};
