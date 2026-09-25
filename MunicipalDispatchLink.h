#ifndef MUNICIPAL_DISPATCH_LINK_H
#define MUNICIPAL_DISPATCH_LINK_H

#include <string>

class MunicipalDispatchLink {
public:
    MunicipalDispatchLink();
    int submitDispatchTicket(const std::string& ticket, int urgencyCode);

private:
    bool linkIsUp;
};

#endif
