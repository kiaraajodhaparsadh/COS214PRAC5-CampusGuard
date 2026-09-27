#ifndef MUNICIPAL_SERVICE_ADAPTER_H
#define MUNICIPAL_SERVICE_ADAPTER_H

#include "ExternalAssistanceService.h"
#include "MunicipalDispatchLink.h"

class MunicipalServiceAdapter : public ExternalAssistanceService {
public:
    MunicipalServiceAdapter();
    ~MunicipalServiceAdapter() override;
    MunicipalServiceAdapter(const MunicipalServiceAdapter&) = delete;
    MunicipalServiceAdapter& operator=(const MunicipalServiceAdapter&) = delete;

    AssistanceOutcome requestAssistance(const std::string& incidentId, const std::string& incidentType, const std::string& areaName) override;

private:
    MunicipalDispatchLink* dispatchLink;

    static std::string buildLegacyTicket(const std::string& incidentType, const std::string& areaName);
    static int mapUrgency(const std::string& incidentType);
    static AssistanceOutcome translateStatus(int legacyStatus);
};

#endif
