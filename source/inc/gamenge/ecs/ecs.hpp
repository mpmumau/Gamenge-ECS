#ifndef GAMENGE_ECS_ECS_H
#define GAMENGE_ECS_ECS_H

#include <forward_list>

#include <gamenge/ecs/ecs_common.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>
#include <gamenge/ecs/system_manager.hpp>

namespace Gamenge {
    /**
     * @brief  Primary class for interacting with the ECS.
     */
    class ECS {
    public:
        /**
         * @brief  Add an entity to the ECS.
         * 
         * @return  eid  The EID of the entity.
         */
        EID addEntity();

        /**
         * @brief Get the Mask of a given entity.
         * 
         * @param  eid  The EID of the entity to get.
         * 
         * @return  The Mask of the given entity.
         */
        Mask getEntity(EID);

        /**
         * @brief Remove an entity from the ECS.
         * 
         * @param  eid  The EID of the entity to remove.
         */
        void removeEntity(EID);

        /**
         * @brief Determine whether or not an entity is enabled.
         * 
         * @param  eid  The EID of the entity to check.
         * @return  A boolean representing whether or not the entity is enabled.
         */
        bool isEnabled(EID);

        /**
         * @brief  Add a component for the given entity, with the given mask as identification.
         * 
         * @param  eid  The EID of the entity to which you will add the component.
         * @param  mask  The mask for the component.
         * @param  component  A pointer to a dynamically allocated component.
         */
        void addComponent(EID, Mask, Component *);

        /**
         * @brief  Get the component of the given EID at the given mask.
         * 
         * @param  eid  The EID of the entity.
         * @param  Mask  The mask of the component to be retrieved.
         * 
         * @return A generic Component pointer to the component.
         */
        Component *getComponent(EID, Mask);

        /**
         * @brief Remove a component of the given mask from the given EID.
         * 
         * @param  EID  The EID of the entity for which to remove the component.
         * @param  Mask  The mask of the component to remove.
         */
        void removeComponent(EID, Mask);

        /**
         * @brief  Add a system to the ECS.
         * 
         * @param  system  A pointer to a system object.
         */
        void addSystem(System *);

        /**
         * @brief  Remove a system from the ECS.
         * 
         * @param  The mask of the system to remove.
         */
        void removeSystem(System *);

        /**
         * @brief  Send a message through the ECS. 
         * 
         * @param  message  A pointer to a message object to send. Note that the target of the message should be set on the message object.
         */
        void sendMessage(Message *);

        /**
         * @brief  Tick the ECS one step forward.
         * 
         * @param  delta  The amount of nanoseconds represented by the tick.
         */
        void tick(Nanos);

        /**
         * @brief Destroy the ECS and all of its associated resources.
         */
        void destroy();
    private:
        EntityManager entityManager;
        ComponentManager componentManager;
        SystemManager systemManager;

        std::forward_list<Message *> messages;
        void dispatchMessages();
        void destroyMessages();
    };

} // end namespace Gamenge

#endif