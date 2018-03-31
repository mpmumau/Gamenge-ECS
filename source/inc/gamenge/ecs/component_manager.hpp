#ifndef GAMENGE_ECS_COMPONENT_MANAGER_H
#define GAMENGE_ECS_COMPONENT_MANAGER_H

#include <map>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

namespace Gamenge {

    class ComponentManager {
    public:
        ComponentManager();
        ~ComponentManager();

        void addComponent(EID, Mask, Component *);
        Component *getComponent(EID, Mask);
        void removeComponent(EID, Mask);
        void clearEntity(EID);

        void receiveMessage(Message *);

        ComponentBundle getComponentBundle(EID, Mask);
        ComponentBundle getComponentBundle(EID, Mask, bool);
        void destroy();
    private:
        typedef Component * ComponentGroup[ECS_MAX_ENTITIES];

        std::map<Mask, ComponentGroup> componentGroups;
        
        void createComponentGroup(Mask);
    };

}

#endif