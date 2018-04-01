#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/component_manager.hpp>

using namespace Gamenge;

ComponentManager::ComponentManager()
{
    for (EID eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
        addComponent(eid, Mask(0x00), new MessagingComponent());
    }
}

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
    if (mask == Mask(0x00) ||
        componentGroups.count(mask) == 0 ||
        componentGroups[mask][eid] == NULL
    ) {
        return;
    }

    delete componentGroups[mask][eid];
    componentGroups[mask][eid] = NULL;
}

void ComponentManager::clearEntity(EID eid)
{
    for (auto it = componentGroups.begin(); it != componentGroups.end(); ++it) {
        if (it->first == Mask(0x00) ||
            it->second[eid] == NULL
        ) {
            continue;
        }

        delete it->second[eid];
        it->second[eid] = NULL;
    }
}

void ComponentManager::receiveMessage(Message *message)
{
    MessagingComponent *messagingComponent = dynamic_cast<MessagingComponent *>(getComponent(message->target, Mask(0x00)));
    messagingComponent->receiveMessage(message);
}

void ComponentManager::clearAllMessages()
{
    for (EID eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
        MessagingComponent *messagingComponent = dynamic_cast<MessagingComponent *>(getComponent(eid, Mask(0x00)));
        messagingComponent->messages.clear();
    }
}

ComponentBundle ComponentManager::getComponentBundle(EID eid, Mask mask)
{
    return getComponentBundle(eid, mask, false);
}

ComponentBundle ComponentManager::getComponentBundle(EID eid, Mask mask, bool includeMessaging)
{
    ComponentBundle componentBundle;

    for (auto it = componentGroups.begin(); it != componentGroups.end(); ++it) {
        if (MaskUtils::matchesAny(it->first, mask)) {
            componentBundle[it->first] = it->second[eid];
        }
    }

    if (includeMessaging) {
        try {
            componentBundle[Mask(0x00)] = componentGroups.at(Mask(0x00))[eid];
        } catch (const std::out_of_range& e) {
            throw e;
        }
    }

    return componentBundle;
}

void ComponentManager::destroy()
{
    for (auto it = componentGroups.begin(); it != componentGroups.end(); ++it) {
        for (EID eid = 0; eid < ECS_MAX_ENTITIES; eid++) {
            if (it->second[eid] == NULL) {
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