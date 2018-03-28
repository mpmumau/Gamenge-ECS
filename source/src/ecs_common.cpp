#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

bool MaskUtils::matches(Mask needle, Mask haystack)
{
    return (needle & haystack) == haystack;
}

bool MaskUtils::matchesAny(Mask needle, Mask haystack)
{
    return (needle & haystack) != 0;
}