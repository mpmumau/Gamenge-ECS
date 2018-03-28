#ifndef GAMENGE_ECS_ECS_DEF
#define GAMENGE_ECS_ECS_DEF

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>

using namespace Gamenge;

namespace Gamenge {
    class ECS {
    public:
        EID addEntity();
        Mask getEntity(EID);
        void removeEntity(EID);
        bool isEnabled(EID);
        void addComponent(EID, Mask, Component *);
        Component *getComponent(EID, Mask);
        void removeComponent(EID, Mask);
        void destroy();
    private:
        EntityManager entityManager;
        ComponentManager componentManager;
    };

} // end namespace Gamenge

#endif