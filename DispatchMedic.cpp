#include "DispatchMedic.h"
#include "MedicTeam.h"

DispatchMedic::DispatchMedic(MedicTeam *receiver, std::string loc, int sev)
    : receiver(receiver), location(loc), triageLevel(sev), previousState(nullptr) {}

DispatchMedic::~DispatchMedic()
{
    delete previousState;
}

void DispatchMedic::execute()
{
    previousState = receiver->createMemento();
    receiver->dispatch(location);
}

void DispatchMedic::undo()
{
    if (previousState != nullptr)
    {
        receiver->restore(previousState);
    }
}