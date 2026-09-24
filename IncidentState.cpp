#include "IncidentState.h"
#include "Incident.h"
#include <iostream>


static void refuse(const Incident *incident, const std::string &action)
{
    std::cout << "[Incident " << incident->getIncidentID() << "] Cannot " << action
              << " - incident is currently " << incident->getStateName() << ".\n";
}

// ---------------------------------------------------------------- Reported
IncidentState *ReportedState::instance()
{
    static ReportedState instance;
    return &instance;
}

bool ReportedState::dispatchUnit(Incident *incident)
{
    incident->setState(RespondingState::instance());
    std::cout << "[Incident " << incident->getIncidentID() << "] Reported -> Responding (first unit dispatched).\n";
    return true;
}

bool ReportedState::escalate(Incident *incident)
{
    refuse(incident, "escalate off-campus"); // nobody has responded yet
    return false;
}

bool ReportedState::contain(Incident *incident)
{
    refuse(incident, "be marked as contained"); // nothing is being actively managed yet
    return false;
}

bool ReportedState::resolve(Incident *incident)
{
    refuse(incident, "be resolved"); // can't skip straight from reported to resolved
    return false;
}

// -------------------------------------------------------------- Responding
IncidentState *RespondingState::instance()
{
    static RespondingState instance;
    return &instance;
}

bool RespondingState::dispatchUnit(Incident *incident)
{
    // Additional units can be sent while already responding - this is a
    // legal no-op transition (stays Responding), not a refusal.
    std::cout << "[Incident " << incident->getIncidentID() << "] Additional unit dispatched while Responding.\n";
    return true;
}

bool RespondingState::escalate(Incident *incident)
{
    std::cout << "[Incident " << incident->getIncidentID() << "] Escalating off-campus while Responding.\n";
    return true; // legal: campus resources are engaged but insufficient
}

bool RespondingState::contain(Incident *incident)
{
    incident->setState(ContainedState::instance());
    std::cout << "[Incident " << incident->getIncidentID() << "] Responding -> Contained.\n";
    return true;
}

bool RespondingState::resolve(Incident *incident)
{
    refuse(incident, "be resolved"); // must be contained first
    return false;
}

// --------------------------------------------------------------- Contained
IncidentState *ContainedState::instance()
{
    static ContainedState instance;
    return &instance;
}

bool ContainedState::dispatchUnit(Incident *incident)
{
    refuse(incident, "dispatch new units"); // the situation is already under control
    return false;
}

bool ContainedState::escalate(Incident *incident)
{
    // Rare but legal: a contained incident can still need outside help
    // (e.g. specialist cleanup), so escalation is not refused here.
    std::cout << "[Incident " << incident->getIncidentID() << "] Escalating off-campus while Contained.\n";
    return true;
}

bool ContainedState::contain(Incident *incident)
{
    refuse(incident, "be marked as contained again"); // already contained
    return false;
}

bool ContainedState::resolve(Incident *incident)
{
    incident->setState(ResolvedState::instance());
    std::cout << "[Incident " << incident->getIncidentID() << "] Contained -> Resolved.\n";
    return true;
}

// ----------------------------------------------------------------- Resolved
IncidentState *ResolvedState::instance()
{
    static ResolvedState instance;
    return &instance;
}

bool ResolvedState::dispatchUnit(Incident *incident)
{
    refuse(incident, "dispatch units"); // this is the headline failure case
    return false;
}

bool ResolvedState::escalate(Incident *incident)
{
    refuse(incident, "escalate off-campus");
    return false;
}

bool ResolvedState::contain(Incident *incident)
{
    refuse(incident, "be marked as contained");
    return false;
}

bool ResolvedState::resolve(Incident *incident)
{
    refuse(incident, "be resolved again");
    return false;
}
