#ifndef GAMENGE_ECS_SYSTEM_H
#define GAMENGE_ECS_SYSTEM_H

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class System {
    public:
        System(Mask, unsigned short);
        virtual ~System() {};
        
        Mask getMask();
        unsigned short getSortOrder();
        virtual void tick(Nanos, EID, ComponentBundle) = 0;
    protected:
        Mask mask;
        unsigned short sortOrder;
    };

}

#endif