#ifndef GAMENGE_ECS_SYSTEM_H
#define GAMENGE_ECS_SYSTEM_H

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class System {
    public:
        System(Mask, unsigned short);
        System(Mask, unsigned short, bool);
        virtual ~System() {};
        
        Mask getMask();
        unsigned short getSortOrder();
        bool usesMessaging();

        virtual void tick(Nanos, EID, ComponentBundle) = 0;
    protected:
        Mask mask;
        bool messaging;
        unsigned short sortOrder;
    };

}

#endif