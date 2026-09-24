#include "CommunicationService.h"
#include "ComponentStateMemento.h"

CommunicationService::CommunicationService(ResponseCoordinator *mediator, std::string id)
    : ResponseComponent(mediator, id) {}

void CommunicationService::dispatch(std::string location)
{
    // dispatch just sends a generic warning to a specific location
    std::string msg = "WARNING: Emergency situation reported at " + location + ". Please avoid the area.";
    broadcastMessage(msg);
}

void CommunicationService::broadcastMessage(std::string message)
{
    broadcastLog.push_back(message);
    this->status = OperationalStatus::Active;

    //  notify the mediator in case they need to log that a message went out
    if (mediator)
    {
        mediator->notify(this, "MessageBroadcasted");
    }
}

// so this is an example of how this can be used in mediator:
/*void CampusControlRoom::notify(ResponseComponent *sender, std::string event)
{
    if (event == "MultiDoorLockdown")
    {
        // Facilities just locked down. Automatically tell Comms to announce it!
        commsService->broadcastMessage("Campus is in full lockdown. Stay in your classrooms.");
    }
    else if (event == "WeaponsAuthorized")
    {
        commsService->broadcastMessage("Lethal force authorized on campus. Evacuate immediately.");
    }
}*/

void CommunicationService::displayStatus()
{
    const std::string MAGENTA = "\033[35m";
    const std::string RESET = "\033[0m";

    std::string statusStr = (status == OperationalStatus::Active) ? "Transmitting" : "Standby";

    std::cout << MAGENTA << "=== [COMMUNICATIONS: " << componentID << "] ===" << RESET << "\n";
    std::cout << MAGENTA << " > Status: " << RESET << statusStr << "\n";
    std::cout << MAGENTA << " > Recent Broadcasts:\n"
              << RESET;

    if (broadcastLog.empty())
    {
        std::cout << "   (No messages broadcasted yet)\n";
    }
    else
    {
        // Print the last few messages
        for (const std::string &msg : broadcastLog)
        {
            std::cout << "   - \"" << msg << "\"\n";
        }
    }
    std::cout << MAGENTA << "======================================" << RESET << "\n\n";
}

ComponentStateMemento *CommunicationService::createMemento()
{
    return new ComponentStateMemento(componentID, status, broadcastLog);
}
void CommunicationService::restore(ComponentStateMemento *memento)
{

    if (!memento)
    {
        return;
    }

    this->componentID = memento->componentID;
    this->status = memento->status;

    this->broadcastLog = memento->broadcastLog;

    std::cout
        << "[CommunicationService: " + componentID + " ] Reverted to previous state successfully. Broadcast logs updated.\n";
}