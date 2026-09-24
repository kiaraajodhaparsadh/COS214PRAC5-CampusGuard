#include "ComponentState.h"

ComponentState *IdleState::instance()
{
    static IdleState instance;
    return &instance;
}

ComponentState *ActiveState::instance()
{
    static ActiveState instance;
    return &instance;
}

ComponentState *OfflineState::instance()
{
    static OfflineState instance;
    return &instance;
}

ComponentState *ComponentState::fromEnum(OperationalStatus status)
{
    switch (status)
    {
    case OperationalStatus::Idle:
        return IdleState::instance();
    case OperationalStatus::Active:
        return ActiveState::instance();
    case OperationalStatus::Offline:
        return OfflineState::instance();
    }
    // unreachable, but keeps every compiler happy
    return IdleState::instance();
}
