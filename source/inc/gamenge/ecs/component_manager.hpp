#ifndef GAMENGE_ECS_COMPONENT_MANAGER_H
#define GAMENGE_ECS_COMPONENT_MANAGER_H

#include <map>

#include <gamenge/ecs/ecs.hpp>

namespace Gamenge {

    class ComponentManager {
    public:
        void addComponent(EID, Mask, Component *);
        Component *getComponent(EID, Mask);
        void removeComponent(EID, Mask);
        ComponentBundle getComponentBundle(EID, Mask);
        void destroy();
    private:
        typedef Component * ComponentGroup[ECS_MAX_ENTITIES];
        std::map<Mask, ComponentGroup> componentGroups;
        void createComponentGroup(Mask);
    };

}

#endif