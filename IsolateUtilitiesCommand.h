#pragma once
#include "ResponseAction.h"
#include "FacilitiesTeam.h"
#include "ComponentStateMemento.h"
#include <string>

class IsolateUtilitiesCommand : public ResponseAction
{
private:
    FacilitiesTeam *receiver;
    std::string targetLocation;
    ComponentStateMemento *previousState;

public:
    IsolateUtilitiesCommand(FacilitiesTeam *receiver, std::string location);
    ~IsolateUtilitiesCommand() override;

    void execute() override;
    void undo() override;
};