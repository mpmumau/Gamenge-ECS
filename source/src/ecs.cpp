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

void ECS::addSystem(System *system)
{
    systemManager.addSystem(system);
}

void ECS::removeSystem(Mask mask)
{
    systemManager.removeSystem(mask);
}

void ECS::sendMessage(Message *message)
{
    messages.push_front(message);
}

bool ECS::isEnabled(EID eid)
{
    return entityManager.isEnabled(eid);
}

void ECS::tick(Nanos delta)
{
    dispatchMessages();
    systemManager.tick(delta, &entityManager, &componentManager);
    destroyMessages();
}

void ECS::destroy()
{
    componentManager.destroy();
    systemManager.destroy();
    destroyMessages();
}

void ECS::dispatchMessages()
{
    for (auto it = messages.begin(); it != messages.end(); ++it) {
        componentManager.receiveMessage(*it);
    }
}

void ECS::destroyMessages()
{
    for (auto it = messages.begin(); it != messages.end(); ++it) {
        if (*it == NULL) {
            continue;
        }

        delete *it;
        *it = NULL;
    }

    messages.clear();
}