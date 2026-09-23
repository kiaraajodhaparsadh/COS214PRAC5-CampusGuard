// concrete command

#pragma once
#include "ResponseAction.h" // command interface
#include <string>

class ResponseComponent; // recievers

class DispatchSecurity : public ResponseAction
{
private:
    SecurityTeam *receiver;
    std::string location;

public:
    DispatchSecurity(ResponseComponent *receiver, std::string location);
    ~DispatchSecurity() override = default;

    void execute() override;
};
