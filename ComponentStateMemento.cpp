#include "ComponentStateMemento.h"

// 1. Facilities constructor
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, const std::map<std::string, bool> &doors)
    : componentID(id), status(status), location(""), facilityDoors(doors),
      medicsAvailable(0), triageLevel(0), weaponsDeployed(false), broadcastLog() {}

// 2. MedicTeam constructor
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, int medics, int triage)
    : componentID(id), status(status), location(loc), facilityDoors(),
      medicsAvailable(medics), triageLevel(triage), weaponsDeployed(false), broadcastLog() {}

// 3. SecurityTeam constructor
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, bool weapons)
    : componentID(id), status(status), location(loc), facilityDoors(),
      medicsAvailable(0), triageLevel(0), weaponsDeployed(weapons), broadcastLog() {}

// 4. CommunicationService constructor
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, const std::vector<std::string> &logs)
    : componentID(id), status(status), location(""), facilityDoors(),
      medicsAvailable(0), triageLevel(0), weaponsDeployed(false), broadcastLog(logs) {}

ComponentStateMemento::~ComponentStateMemento() = default;