#ifndef GAMENGE_ENTITY_MANAGER_H
#define GAMENGE_ENTITY_MANAGER_H

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

namespace Gamenge {

    class EntityManager {
    public:
        EntityManager();

        EID addEntity();
        void removeEntity(EID);
        void addMask(EID, Mask);
        Mask getMask(EID);
        void removeMask(EID, Mask);
        bool isEnabled(EID);

    private:
        Entity entities[ECS_MAX_ENTITIES];
        EID nextEntity;

        void incrementNextEntity();
    };

} // end namespace Gamenge

#endif