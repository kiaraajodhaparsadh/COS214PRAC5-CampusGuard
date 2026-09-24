#pragma once
#include <string>
#include "ResponseComponent.h" // needed for the OperationalStatus enum

// STATE PARTICIPANT
// Governs what a ResponseComponent is currently allowed to do. Replaces the
// bare OperationalStatus enum as the thing that actually decides behaviour;
// the enum itself is kept only as the plain, serialisable value that
// ComponentStateMemento stores, so Memento never has to know this class exists.
class ComponentState
{
public:
    virtual ~ComponentState() = default;

    // The one rule every concrete component currently needs: can this
    // component legally accept a new dispatch order right now?
    virtual bool canDispatch() const = 0;

    // Lets a component turn its current state into the enum Memento stores.
    virtual OperationalStatus toEnum() const = 0;

    // Human-readable name for status prints.
    virtual std::string name() const = 0;

    // Maps a memento's stored enum back onto the matching state singleton.
    // This is how restore() re-enters the State pattern from a plain enum.
    static ComponentState *fromEnum(OperationalStatus status);
};

// CONCRETE STATES
// Each is stateless, so each is implemented as a static singleton rather
// than something ResponseComponent news and deletes. ResponseComponent's
// `state` pointer is therefore always non-owning - never delete it.

class IdleState : public ComponentState
{
public:
    static ComponentState *instance();
    bool canDispatch() const override { return true; }
    OperationalStatus toEnum() const override { return OperationalStatus::Idle; }
    std::string name() const override { return "Idle"; }
};

class ActiveState : public ComponentState
{
public:
    static ComponentState *instance();
    // an already-active component can still be redirected to a new location
    bool canDispatch() const override { return true; }
    OperationalStatus toEnum() const override { return OperationalStatus::Active; }
    std::string name() const override { return "Active"; }
};

class OfflineState : public ComponentState
{
public:
    static ComponentState *instance();
    // depleted/offline components refuse new orders until someone resets them
    bool canDispatch() const override { return false; }
    OperationalStatus toEnum() const override { return OperationalStatus::Offline; }
    std::string name() const override { return "Offline"; }
};
