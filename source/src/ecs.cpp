#include <stdio.h>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>
#include <gamenge/ecs/system_manager.hpp>

#include <gamenge/ecs/ecs.hpp>

using namespace Gamenge;

EID ECS::addEntity()
{
    return entityManager.addEntity();
}

Mask ECS::getEntity(EID eid)
{
    return entityManager.getMask(eid);
}

void ECS::removeEntity(EID eid)
{
    componentManager.clearEntity(eid);
    entityManager.removeEntity(eid);
}

void ECS::addComponent(EID eid, Mask mask, Component *component)
{
    componentManager.addComponent(eid, mask, component);
    entityManager.addMask(eid, mask);
}

Component *ECS::getComponent(EID eid, Mask mask)
{
    return componentManager.getComponent(eid, mask);
}

void ECS::removeComponent(EID eid, Mask mask)
{
    componentManager.removeComponent(eid, mask);
    entityManager.removeMask(eid, mask);
}

bool ECS::isEnabled(EID eid)
{
    return entityManager.isEnabled(eid);
}

void ECS::tick(Nanos delta)
{
    systemManager.tick(delta, &entityManager, &componentManager);
}

void ECS::destroy()
{
    componentManager.destroy();
    systemManager.destroy();
}