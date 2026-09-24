#pragma once
#include "ResponseComponent.h"
#include "ResponseCoordinator.h"
#include <string>
#include <vector>
#include <iostream>

class CommunicationService : public ResponseComponent
{
private:
    std::vector<std::string> broadcastLog; // history of sent messages

public:
    CommunicationService(ResponseCoordinator *mediator, std::string id);
    ~CommunicationService() override = default;

    // Overrides
    void dispatch(std::string location) override;
    void displayStatus() override;
    ComponentStateMemento *createMemento() override;
    void restore(ComponentStateMemento *memento) override;

    // Specific method for sending custom alerts
    void broadcastMessage(std::string message);
};