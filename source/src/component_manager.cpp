#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/component_manager.hpp>

using namespace Gamenge;

void ComponentManager::addComponent(EID eid, Mask mask, Component *component)
{
    if (componentGroups.count(mask) == 0) {
        createComponentGroup(mask);
    }

    componentGroups[mask][eid] = component;
}

Component *ComponentManager::getComponent(EID eid, Mask mask)
{
    return componentGroups[mask][eid];
}

void ComponentManager::removeComponent(EID eid, Mask mask)
{
    if (componentGroups[mask][eid] != NULL) {
        delete componentGroups[mask][eid];
    }
    componentGroups[mask][eid] = NULL;
}

void ComponentManager::clearEntity(EID eid)
{
    for (std::map<Mask, ComponentGroup>::iterator it = componentGroups.begin();
        it != componentGroups.end();
        ++it
    ) {
        if (it->second[eid] == NULL) {
            continue;
        }
        delete it->second[eid];
        it->second[eid] = NULL;
    }
}

ComponentBundle ComponentManager::getComponentBundle(EID eid, Mask mask)
{
    ComponentBundle componentBundle;

    for (std::map<Mask, ComponentGroup>::iterator it = componentGroups.begin();
        it != componentGroups.end();
        ++it
    ) {
        if (MaskUtils::matchesAny(it->first, mask)) {
            componentBundle[it->first] = it->second[eid];
        }
    }

    return componentBundle;
}

void ComponentManager::destroy()
{
    Component * component;

    for (std::map<Mask, ComponentGroup>::iterator it = componentGroups.begin();
        it != componentGroups.end();
        ++it
    ) {
        for (int i = 0; i < ECS_MAX_ENTITIES; i++) {
            component = it->second[i];
            if (component != NULL) {
                delete it->second[i];
            }
            it->second[i] = NULL;
        }
    }
}

void ComponentManager::createComponentGroup(Mask mask)
{
    for (unsigned int i = 0; i < ECS_MAX_ENTITIES; i++) {
        componentGroups[mask][i] = NULL;
    }
}