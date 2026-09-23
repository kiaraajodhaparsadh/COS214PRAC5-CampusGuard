#pragma once
#include <string>
// COLLEGUE PARTICIPANT
class ResponseCoordinator;   // mediator
class ComponentStateMemento; // memento

enum class OperationalStatus
{
    Idle,
    EnRoute,
    Active,
    Offline
};

class ResponseComponent
{
protected:
    ResponseCoordinator *mediator; // every collegue knows the mediator
    std::string componentID;       // like a unique name or id(MainGates, SecurityTeam1, ect)

    OperationalStatus status; // enum for their state
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
