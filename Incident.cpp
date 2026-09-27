#include "Incident.h"
#include "IncidentState.h"

Incident::Incident(std::string id, std::string type, int severity, std::string location)
    : incidentID(id), type(type), severity(severity), location(location),
      state(ReportedState::instance()) {}

bool Incident::dispatchUnit() { return state->dispatchUnit(this); }
bool Incident::escalate() { return state->escalate(this); }
bool Incident::contain() { return state->contain(this); }
bool Incident::resolve() { return state->resolve(this); }

void Incident::setState(IncidentState *newState)
{
    if (newState != nullptr)
    {
        state = newState;
    }
}

std::string Incident::getStateName() const
{
    return state->name();
}
