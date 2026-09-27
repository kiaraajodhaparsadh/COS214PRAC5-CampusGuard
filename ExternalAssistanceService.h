#ifndef EXTERNAL_ASSISTANCE_SERVICE_H
#define EXTERNAL_ASSISTANCE_SERVICE_H

#include <string>

enum class AssistanceOutcome {
    Accepted,
    Rejected,
    Unavailable
};

class ExternalAssistanceService {
public:
    virtual ~ExternalAssistanceService() = default;
    virtual AssistanceOutcome requestAssistance(const std::string& incidentId, const std::string& incidentType, const std::string& areaName) = 0;  //pure
};

#endif
