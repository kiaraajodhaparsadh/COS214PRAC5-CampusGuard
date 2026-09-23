// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include <string>

class ResponseComponent; // recievers

class DispatchMedic : public ResponseAction
{
private:
    MedicTeam *receiver; // Point directly to MedicTeam instead of the base class
    std::string location;
    int triageLevel;

public:
    DispatchMedic(MedicTeam *receiver, std::string loc, int sev)
        : receiver(receiver), location(loc), triageLevel(sev) {}

    void execute() override
    {
        receiver->dispatch(location); // call a specific MedicTeam method
    }
};