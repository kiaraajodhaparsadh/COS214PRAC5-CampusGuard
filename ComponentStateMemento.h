#pragma once
#include <string>
#include <vector>
#include <map>
#include "ResponseComponent.h" // Needed for OperationalStatus enum

// recievers or originators
class FacilitiesControlService;
class MedicTeam;
class SecurityTeam;
class CommunicationService;

class ComponentStateMemento
{
private:
    // narrow interface: private, so caretakers cannot edit data

    // all possible member variables
    std::string componentID;
    OperationalStatus status;
    std::string location;

    // Subsystem-specific state
    std::map<std::string, bool> facilityDoors; // FacilitiesControlService
    int medicsAvailable;                       // MedicTeam
    int triageLevel;                           // MedicTeam
    bool weaponsDeployed;                      // SecurityTeam
    std::vector<std::string> broadcastLog;     // CommunicationService

    // Constructors for different components
    // Declarations only
    ComponentStateMemento(std::string id, OperationalStatus status, const std::map<std::string, bool> &doors);
    ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, int medics, int triage);
    ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, bool weapons);
    ComponentStateMemento(std::string id, OperationalStatus status, const std::vector<std::string> &logs);

    // wide interface, only allow originators to access private fields
    friend class FacilitiesControlService;
    friend class MedicTeam;
    friend class SecurityTeam;
    friend class CommunicationService;

public:
    // public narrow interface for the Caretaker
    virtual ~ComponentStateMemento();
};