#pragma once
#include <string>

// MEDIATOR PARTICIPANT
class ResponseComponent; // colleague

class ResponseCoordinator
{
public:
    ResponseCoordinator() = default;
    virtual ~ResponseCoordinator() = default;

    // Every colleague calls this on itself when something worth coordinating
    // happens. sender lets the mediator work out who raised it; event is a
    // short domain string ("Dispatched", "LockdownAllDoors", ...).
    virtual void notify(ResponseComponent *sender, std::string event) = 0;
};
