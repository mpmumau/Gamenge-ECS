#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/component_manager.hpp>

using namespace Gamenge;

ComponentManager::~ComponentManager()
{
    destroy();
}

void ComponentManager::addComponent(EID eid, Mask mask, Component *component)
{
    if (componentGroups.count(mask) == 0) {
        createComponentGroup(mask);
    }

    componentGroups[mask][eid] = component;
}

Component *ComponentManager::getComponent(EID eid, Mask mask)
{
    if (componentGroups.count(mask) == 0) {
        return NULL;
    }

    return componentGroups[mask][eid];
}

void ComponentManager::removeComponent(EID eid, Mask mask)
{
    if (componentGroups.count(mask) == 0 || componentGroups[mask][eid] == NULL) {
        return;
    }

    delete componentGroups[mask][eid];
    componentGroups[mask][eid] = NULL;
}

void ComponentManager::clearEntity(EID eid)
{
    for (auto it = componentGroups.begin(); it != componentGroups.end(); ++it) {
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

    for (auto it = componentGroups.begin(); it != componentGroups.end(); ++it) {
        if (MaskUtils::matchesAny(it->first, mask)) {
            componentBundle[it->first] = it->second[eid];
        }
    }

    return componentBundle;
}

void ComponentManager::destroy()
{
    Component *component;

    for (auto it = componentGroups.begin(); it != componentGroups.end(); ++it) {
        for (EID eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
            component = it->second[eid];
            if (component == NULL) {
                continue;
            }
            delete it->second[eid];
            it->second[eid] = NULL;
        }
    }
}

void ComponentManager::createComponentGroup(Mask mask)
{
    for (EID eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
        componentGroups[mask][eid] = NULL;
    }
}