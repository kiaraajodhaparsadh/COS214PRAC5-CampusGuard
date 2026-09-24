#include "ComponentStateMemento.h"

// 1. AccessControlService Snapshot
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, const std::map<std::string, bool> &doors)
    : componentID(id), status(status), location(""), facilityDoors(doors),
      availableMaintenanceCrews(0), isolatedUtilities(), medicsAvailable(0), triageLevel(0),
      weaponsDeployed(false), broadcastLog() {}

// 2. FacilitiesTeam Snapshot
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, int maintenanceCrews, const std::map<std::string, bool> &utilities)
    : componentID(id), status(status), location(""), facilityDoors(),
      availableMaintenanceCrews(maintenanceCrews), isolatedUtilities(utilities), medicsAvailable(0), triageLevel(0),
      weaponsDeployed(false), broadcastLog() {}

// 3. MedicTeam Snapshot
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, int medics, int triage)
    : componentID(id), status(status), location(loc), facilityDoors(),
      availableMaintenanceCrews(0), isolatedUtilities(), medicsAvailable(medics), triageLevel(triage),
      weaponsDeployed(false), broadcastLog() {}

// 4. SecurityTeam Snapshot
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, std::string loc, bool weapons)
    : componentID(id), status(status), location(loc), facilityDoors(),
      availableMaintenanceCrews(0), isolatedUtilities(), medicsAvailable(0), triageLevel(0),
      weaponsDeployed(weapons), broadcastLog() {}

// 5. CommunicationService Snapshot
ComponentStateMemento::ComponentStateMemento(std::string id, OperationalStatus status, const std::vector<std::string> &logs)
    : componentID(id), status(status), location(""), facilityDoors(),
      availableMaintenanceCrews(0), isolatedUtilities(), medicsAvailable(0), triageLevel(0),
      weaponsDeployed(false), broadcastLog(logs) {}

ComponentStateMemento::~ComponentStateMemento() = default;