// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include <string>

class SecurityTeam;
class ComponentStateMemento;

class DispatchSecurity : public ResponseAction
{
private:
    SecurityTeam *receiver;
    std::string location;
    ComponentStateMemento *previousState;

public:
    DispatchSecurity(SecurityTeam *receiver, std::string location);
    ~DispatchSecurity() override;

    void execute() override;
    void undo() override;
};
