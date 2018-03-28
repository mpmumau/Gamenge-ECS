#ifndef GAMENGE_ENTITY_MANAGER_H
#define GAMENGE_ENTITY_MANAGER_H

#include <gamenge/ecs/ecs.hpp>

using namespace Gamenge;

namespace Gamenge {

    class EntityManager {
    public:
        EntityManager();

        EID addEntity();
        Entity getEntity(EID);
    private:
        Entity entities[ECS_MAX_ENTITIES];
        EID nextEntity;

        void incrementNextEntity();
    };

} // end namespace Gamenge

#endif