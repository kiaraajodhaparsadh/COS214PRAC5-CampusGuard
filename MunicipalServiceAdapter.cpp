#include "MunicipalServiceAdapter.h"
#include <iostream>

MunicipalServiceAdapter::MunicipalServiceAdapter() : dispatchLink(new MunicipalDispatchLink()) {}

MunicipalServiceAdapter::~MunicipalServiceAdapter() {
    delete dispatchLink;
}

std::string MunicipalServiceAdapter::buildLegacyTicket(const std::string& incidentType, const std::string& areaName) {
    return "CampusGuard|" + incidentType + "|" + areaName;
}

int MunicipalServiceAdapter::mapUrgency(const std::string& incidentType) {
    if (incidentType == "Fire" || incidentType == "Medical") return 5;
    if (incidentType == "Security") return 3;
    return 2;
}

AssistanceOutcome MunicipalServiceAdapter::translateStatus(int legacyStatus) {
    switch (legacyStatus) {
        case 200: return AssistanceOutcome::Accepted;
        case 409: return AssistanceOutcome::Rejected;
        default: return AssistanceOutcome::Unavailable;
    }
}

AssistanceOutcome MunicipalServiceAdapter::requestAssistance(const std::string& incidentId, const std::string& incidentType, const std::string& areaName) {
    std::cout << "[MunicipalServiceAdapter] translating request for incident " << incidentId << "\n";
    std::string ticket = buildLegacyTicket(incidentType, areaName);
    int urgency = mapUrgency(incidentType);
    int legacyStatus = dispatchLink->submitDispatchTicket(ticket, urgency);
    return translateStatus(legacyStatus);
}
