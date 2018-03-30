#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/system.hpp>

using namespace Gamenge;

System::System(Mask mask, unsigned short sortOrder)
{
    this->mask = mask;
    this->sortOrder = sortOrder;
}

Mask System::getMask()
{
    return mask;
}

unsigned short System::getSortOrder()
{
    return sortOrder;
}