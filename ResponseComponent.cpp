#include "ResponseComponent.h"
#include "ComponentState.h"

ResponseComponent::ResponseComponent(ResponseCoordinator *mediator, std::string id)
    : mediator(mediator), componentID(id), state(IdleState::instance()) {}

void ResponseComponent::setState(ComponentState *newState)
{
    if (newState != nullptr)
    {
        state = newState;
    }
}

OperationalStatus ResponseComponent::getStatusEnum() const
{
    return state->toEnum();
}

std::string ResponseComponent::getStatusName() const
{
    return state->name();
}
