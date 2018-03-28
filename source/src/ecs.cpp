#include <stdio.h>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs.hpp>

using namespace Gamenge;

bool MaskUtils::matches(Mask needle, Mask haystack)
{
    return (needle & haystack) == haystack;
}

bool MaskUtils::matchesAny(Mask needle, Mask haystack)
{
    return (needle & haystack) != 0;
}

EID ECS::addEntity()
{
    return 12;
}