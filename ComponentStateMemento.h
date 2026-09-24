#pragma once
#include <string>
#include <vector>
#include <map>
#include "ResponseComponent.h" // Needed for OperationalStatus enum

// recievers or originators
class AccessControlService;
class MedicTeam;
class SecurityTeam;
class CommunicationService;
class FacilitiesTeam;

class ComponentStateMemento
{
private:
    // narrow interface: private, so caretakers cannot edit data

    // all possible member variables
    std::string componentID;
    OperationalStatus status;
    std::string location;
    // Subsystem-specific state
    std::map<std::string, bool> facilityDoors;     // AccessControlService
    int availableMaintenanceCrews;                 // FacilitiesTeam
    std::map<std::string, bool> isolatedUtilities; // FacilitiesTeam
    int medicsAvailable;                           // MedicTeam
    int triageLevel;                               // MedicTeam
    bool weaponsDeployed;                          // SecurityTeam
    std::vector<std::string> broadcastLog;         // CommunicationService

    // 1. AccessControlService Constructor
    ComponentStateMemento(std::string id, OperationalStatus status, const std::map<std::string, bool> &doors);

    // 2. FacilitiesTeam Constructor
    ComponentStateMemento(std::string id, OperationalStatus status, int maintenanceCrews, const std::map<std::string, bool> &utilities);

    // 3. MedicTeam Constructor
    ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, int medics, int triage);

    // 4. SecurityTeam Constructor
    ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, bool weapons);

    // 5. CommunicationService Constructor
    ComponentStateMemento(std::string id, OperationalStatus status, const std::vector<std::string> &logs);

        // wide interface, only allow originators to access private fields
    friend class AccessControlService;
    friend class MedicTeam;
    friend class SecurityTeam;
    friend class CommunicationService;
    friend class FacilitiesTeam;

public:
    // public narrow interface for the Caretaker
    virtual ~ComponentStateMemento();
};