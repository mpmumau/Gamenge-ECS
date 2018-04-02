#include <gamenge/common/common.hpp>
#include <gamenge/ecs/system_manager.hpp>

using namespace Gamenge;

SystemManager::~SystemManager()
{
    destroy();
}

void SystemManager::addSystem(System *system)
{
    systems.emplace_front(system);
    systems.sort(sortSystems);
}

void SystemManager::removeSystem(System *system)
{
    if (system == NULL) {
        return;
    }

    delete system;
    systems.remove(system);
}

void SystemManager::tick(Nanos delta, EntityManager *entityManager, ComponentManager *componentManager)
{
    if (entityManager == NULL || componentManager == NULL) {
        return;
    }

    Entity *entities = entityManager->getEntities();
    ComponentBundle componentBundle;
    System *system;

    for (auto it = systems.begin(); it != systems.end(); ++it) {
        system = *it;
        for (EID eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
            if (entities[eid].mask == Mask(0x00) || !entities[eid].enabled) {
                continue;
            }

            if (system->usesMessaging()) {
                componentBundle = componentManager->getComponentBundle(eid, system->getMask(), true);
            } else {
                componentBundle = componentManager->getComponentBundle(eid, system->getMask());
            }
            
            system->tick(delta, eid, componentBundle);
        }
    }
}

unsigned int SystemManager::getNumSystems()
{
    unsigned int size = 0;
    for (auto it = systems.begin(); it != systems.end(); ++it) {
        size++;
    }
    return size;
}

void SystemManager::destroy() 
{
    for (auto it = systems.begin(); it != systems.end(); ++it) {
        if (*it == NULL) {
            continue;
        }
        delete *it;
        *it = NULL;
    }
}

bool SystemManager::sortSystems(System *&system1 , System *&system2)
{
    if (system1->getSortOrder() < system2->getSortOrder()) {
        return true;
    }
    return false;
}