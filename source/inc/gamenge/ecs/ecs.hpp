#ifndef GAMENGE_ECS_ECS_DEF
#define GAMENGE_ECS_ECS_DEF

#include <forward_list>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>
#include <gamenge/ecs/system_manager.hpp>

using namespace Gamenge;

namespace Gamenge {
    class ECS {
    public:
        EID addEntity();
        Mask getEntity(EID);
        void removeEntity(EID);

        void addComponent(EID, Mask, Component *);
        Component *getComponent(EID, Mask);
        void removeComponent(EID, Mask);

        void addSystem(System *);
        void removeSystem(Mask);

        void sendMessage(Message *);

        bool isEnabled(EID);
        void tick(Nanos);
        void destroy();
    private:
        EntityManager entityManager;
        ComponentManager componentManager;
        SystemManager systemManager;

        std::forward_list<Message *> messages;
        void dispatchMessages();
        void destroyMessages();
    };

} // end namespace Gamenge

#endif