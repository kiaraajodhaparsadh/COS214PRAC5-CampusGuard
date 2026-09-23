// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include <string>

class MedicTeam;
class ComponentStateMemento;

class DispatchMedic : public ResponseAction
{
private:
    MedicTeam *receiver; // Point directly to MedicTeam instead of the base class
    std::string location;
    int triageLevel;
    ComponentStateMemento *previousState;

public:
    DispatchMedic(MedicTeam *receiver, std::string loc, int sev);
    ~DispatchMedic() override;

    void execute() override;
    void undo() override;
};