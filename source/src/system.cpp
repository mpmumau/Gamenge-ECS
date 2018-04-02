#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/system.hpp>

using namespace Gamenge;

System::System(Mask mask, unsigned short sortOrder)
{
    this->mask = mask;
    this->sortOrder = sortOrder;
    messaging = false;
}

System::System(Mask mask, unsigned short sortOrder, bool messaging)
{
    this->mask = mask;
    this->sortOrder = sortOrder;
    this->messaging = messaging;
}

Mask System::getMask()
{
    return mask;
}

unsigned short System::getSortOrder()
{
    return sortOrder;
}

bool System::usesMessaging()
{
    return messaging;
}