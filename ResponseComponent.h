#pragma once
#include <string>
// COLLEGUE PARTICIPANT
class ResponseCoordinator;   // mediator
class ComponentStateMemento; // memento

enum class OperationalStatus
{
    Idle,
    Active,
    Offline
};

class ResponseComponent
{
protected:
    ResponseCoordinator *mediator; // every collegue knows the mediator
    std::string componentID;       // like a unique name or id(MainGates, SecurityTeam1, ect)

    OperationalStatus status; // plain domain flag - NOT the GoF State pattern in this
                               // design. That role now belongs to IncidentState. This
                               // stays a simple enum because "can a depleted MedicTeam
                               // be redispatched" is a real check worth keeping, it just
                               // isn't a second State pattern instance.
public:
    ResponseComponent(ResponseCoordinator *mediator, std::string id)
        : mediator(mediator), componentID(id), status(OperationalStatus::Idle) {}
    virtual ~ResponseComponent() = default;

    // pure virtual functions concrete commands will use
    virtual void dispatch(std::string location) = 0;
    virtual void displayStatus() = 0; // prints state of current member variables

    // memento methods needed:
    virtual ComponentStateMemento *createMemento() = 0;
    virtual void restore(ComponentStateMemento *memento) = 0;
};
