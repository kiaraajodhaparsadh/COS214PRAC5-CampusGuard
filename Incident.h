#pragma once
#include <string>

class IncidentState; // state

// CONTEXT PARTICIPANT
// Represents one emergency from report to resolution. Its legality rules
// (can you dispatch to a resolved incident? can you escalate before anyone's
// responding?) live entirely in IncidentState - Incident itself never
// contains an if/else chain over its own status.
class Incident
{
private:
    std::string incidentID;
    std::string type;     // "FIRE", "MEDICAL", "INTRUDER", ...
    int severity;          // 1-5, same scale MedicTeam's triageLevel uses
    std::string location;

    IncidentState *state; // non-owning: always points at a static singleton

public:
    Incident(std::string id, std::string type, int severity, std::string location);
    ~Incident() = default; // nothing owned on the heap, so the default is fine

    // Delegate to the current state. Each returns whether the action was
    // actually allowed to happen - callers (the Mediator, for now) should
    // check the return value rather than assume it always succeeds.
    bool dispatchUnit();
    bool escalate();
    bool contain();
    bool resolve();

    // Called by IncidentState implementations only, to perform a transition.
    void setState(IncidentState *newState);

    std::string getStateName() const;
    std::string getIncidentID() const { return incidentID; }
    std::string getType() const { return type; }
    int getSeverity() const { return severity; }
    std::string getLocation() const { return location; }
};
