#include <stdexcept>

#include <gamenge/ecs/ecs.hpp>
#include <gamenge/ecs/entity_manager.hpp>

using namespace Gamenge;

EntityManager::EntityManager()
{
    for (int eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
        entities[eid] = Entity {0x00, false};
    }

    nextEntity = 0;
}

EID EntityManager::addEntity()
{
    EID eid = nextEntity;
    Entity entity {0x00, true};
    entities[eid] = entity;
    incrementNextEntity();
    return eid;
}

Entity EntityManager::getEntity(EID eid)
{
    return entities[eid];
}

void EntityManager::incrementNextEntity()
{
    nextEntity++;
    if (nextEntity < ECS_MAX_ENTITIES && !entities[nextEntity].enabled)
        return;

    EID it = ECS_MAX_ENTITIES;
    do {
        it--;
        if(it < 0) {
            throw std::runtime_error("Couldn't add entity; entity container full!");
        }
    } while (entities[it].enabled);
    nextEntity = it;
}
