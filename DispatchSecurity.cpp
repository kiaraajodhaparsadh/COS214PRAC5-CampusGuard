#include "DispatchSecurity.h"
#include "ResponseComponent.h" // Needed so we can call receiver->dispatch()

// Constructor implementation
DispatchSecurity::DispatchSecurity(SecurityTeam *receiver, std::string location)
    : receiver(receiver), location(location) {}

void DispatchSecurity::execute()
{
    // Now location is available to pass to the receiver
    receiver->dispatch(location);
}