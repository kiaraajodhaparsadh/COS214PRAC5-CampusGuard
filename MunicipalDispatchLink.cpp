#include "MunicipalDispatchLink.h"
#include <iostream>

MunicipalDispatchLink::MunicipalDispatchLink() : linkIsUp(true) {}

int MunicipalDispatchLink::submitDispatchTicket(const std::string& ticket, int urgencyCode) {
    std::cout << "[MunicipalDispatchLink] legacy ticket received: " << ticket << " urgency=" << urgencyCode << "\n";

    if (!linkIsUp) {
        return -1;
    }
    if (urgencyCode < 1 || urgencyCode > 5) {
        return 500;
    }
    if (ticket.find("Security") != std::string::npos && urgencyCode < 4) {
        return 409;
    }
    return 200;
}
