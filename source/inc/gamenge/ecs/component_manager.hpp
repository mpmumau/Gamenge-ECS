#ifndef GAMENGE_ECS_COMPONENT_MANAGER_H
#define GAMENGE_ECS_COMPONENT_MANAGER_H

#include <unordered_map>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

namespace Gamenge {

    /**
     * @brief  An object responsible for handling Components within the ECS.
     */
    class ComponentManager {
    public:
        /**
         * @brief Construct the ComponentManager.
         */
        ComponentManager();

        /**
         * @brief Destroy the ComponentManager object and release its resources.
         */
        ~ComponentManager();

        /**
         * @brief  Add a Component to the Entity.
         * 
         * @param  eid  The entity to which to add the component.
         * @param  mask  The Mask of the Component to add.
         * @param  component  A pointer to the component object to add.
         */
        void addComponent(EID, Mask, Component *);

        /**
         * @brief  Get a Component pointer for the Entity, as specified by the Mask value.
         * 
         * @param  eid  The EID of the Entity.
         * @param  mask  The Mask value of the Component to retrieve.
         * 
         * @return A pointer to the Component.
         */
        Component *getComponent(EID, Mask);

        /**
         * @brief  Remove a Component from the Entity, as specified by the Mask value.
         * 
         * @param  eid  The EID of the Entity.
         * @param  mask  The mask of the Component to remove.
         */
        void removeComponent(EID, Mask);

        /**
         * @brief  Clear all Components for the given Entity.
         * 
         * @param  The EID of the Entity to clear.
         */
        void clearEntity(EID);

        /**
         * @brief  Receive a message, and relay it to its target EID MessagingComponent.
         * 
         * @param  A pointer to the Message object.
         */
        void receiveMessage(Message *);

        /**
         * @brief Clears all Message objects in MessagingComponents of all Entities.
         */
        void clearAllMessages();

        /**
         * @brief  Get a ComponentBundle value for the Entity, with Component pointers specified by the Mask.
         * 
         * @param  eid  The EID of the Entity.
         * @param  mask  A Mask value, representing each of the Components to retrieve.
         * 
         * @return  A ComponentBundle value.
         */
        ComponentBundle getComponentBundle(EID, Mask);

        /**
         * @brief  Get a ComponentBundle value for the Entity, with Component pointers specified by 
         * the Mask, optionally including the MessagingComponent.
         * 
         * @param  eid  The EID of the Entity.
         * @param  mask  A Mask value, representing each of the Components to retrieve.
         * @param  includeMessaging  Whether or not to include the MessagingComponent.
         * 
         * @return  A ComponentBundle value, optionally including the MessagingComponent.
         */
        ComponentBundle getComponentBundle(EID, Mask, bool);

        /**
         * @brief  Destroy the ComponentManager and release its resources.
         */
        void destroy();
    private:
        typedef Component * ComponentGroup[ECS_MAX_ENTITIES];

        std::unordered_map<Mask, ComponentGroup> componentGroups;
        
        void createComponentGroup(Mask);
    };

}

#endif