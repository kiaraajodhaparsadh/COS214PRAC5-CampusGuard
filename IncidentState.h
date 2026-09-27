#pragma once
#include <string>

// STATE PARTICIPANT
// Governs what is legal to do to an Incident right now. This is the design's
// one official State pattern instance - it replaces the earlier idea of
// putting State on each ResponseComponent, and instead answers the question
// the scenario actually asks: "registering incidents and changing their
// operational status."
class Incident; // context - forward declared to avoid a circular include

class IncidentState
{
public:
    virtual ~IncidentState() = default;

    // Each returns true if the transition was legal (and performs it by
    // calling incident->setState(...)), or false if it was refused (and
    // prints why, without changing the incident's state).
    virtual bool dispatchUnit(Incident *incident) = 0;
    virtual bool escalate(Incident *incident) = 0;
    virtual bool contain(Incident *incident) = 0;
    virtual bool resolve(Incident *incident) = 0;

    virtual std::string name() const = 0;
};

// CONCRETE STATES
// Stateless, so each is a static singleton rather than something Incident
// news and deletes - Incident::state is always a non-owning pointer.

class ReportedState : public IncidentState
{
public:
    static IncidentState *instance();
    bool dispatchUnit(Incident *incident) override;
    bool escalate(Incident *incident) override;
    bool contain(Incident *incident) override;
    bool resolve(Incident *incident) override;
    std::string name() const override { return "Reported"; }
};

class RespondingState : public IncidentState
{
public:
    static IncidentState *instance();
    bool dispatchUnit(Incident *incident) override;
    bool escalate(Incident *incident) override;
    bool contain(Incident *incident) override;
    bool resolve(Incident *incident) override;
    std::string name() const override { return "Responding"; }
};

class ContainedState : public IncidentState
{
public:
    static IncidentState *instance();
    bool dispatchUnit(Incident *incident) override;
    bool escalate(Incident *incident) override;
    bool contain(Incident *incident) override;
    bool resolve(Incident *incident) override;
    std::string name() const override { return "Contained"; }
};

class ResolvedState : public IncidentState
{
public:
    static IncidentState *instance();
    bool dispatchUnit(Incident *incident) override;
    bool escalate(Incident *incident) override;
    bool contain(Incident *incident) override;
    bool resolve(Incident *incident) override;
    std::string name() const override { return "Resolved"; }
};
