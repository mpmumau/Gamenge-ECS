#include <stdexcept>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/entity_manager.hpp>

using namespace Gamenge;

EntityManager::EntityManager()
{
    for (int eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
        entities[eid] = Entity();
    }

    nextEntity = 0;
}

EID EntityManager::addEntity()
{
    EID eid = nextEntity;
    entities[eid] = Entity(Mask(0x00), true);
    incrementNextEntity();
    return eid;
}

void EntityManager::removeEntity(EID eid)
{
    entities[eid] = Entity(Mask(0x00), false);
}

void EntityManager::addMask(EID eid, Mask mask)
{
    entities[eid].mask = entities[eid].mask | mask;
}

Mask EntityManager::getMask(EID eid)
{
    return entities[eid].mask;
}

void EntityManager::removeMask(EID eid, Mask mask)
{
    entities[eid].mask = entities[eid].mask &~ mask;
}

bool EntityManager::isEnabled(EID eid)
{
    return entities[eid].enabled;
}

Entity *EntityManager::getEntities()
{
    return &entities[0];
}

void EntityManager::incrementNextEntity()
{
    nextEntity++;

    if (nextEntity < ECS_MAX_ENTITIES && 
        !entities[nextEntity].enabled
    ) {
        return;
    }

    EID it = ECS_MAX_ENTITIES;
    
    do {
        it--;
        if (it < 0) {
            throw std::runtime_error("Couldn't add entity; entity container full!");
        }
    } while (entities[it].enabled);

    nextEntity = it;
}
