#ifndef GAMENGE_ECS_ENTITY_MANAGER_H
#define GAMENGE_ECS_ENTITY_MANAGER_H

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

namespace Gamenge {
    /**
     * @brief  Object responsible for handling Entities within the ECS.
     */
    class EntityManager {
    public:
        /**
         * @brief  Initializes the EntityManager object, setting all Entities to disabled with an empty Mask.
         */
        EntityManager();

        /**
         * @brief  Add an Entity.
         * 
         * @return  The EID of the added Entity.
         */
        EID addEntity();

        /**
         * @brief  Remove the Entity with the given EID.
         * 
         * @param  The EID of the Entity to remove.
         */
        void removeEntity(EID);

        /**
         * @brief  Determine whether or not an Entity is enabled.
         * 
         * @param  eid  The EID of the Entity.
         * @return  A boolean representing whether or not the Entity is enabled.
         */
        bool isEnabled(EID);

        /**
         * @brief Add a Mask to the Entity's current Mask.
         * 
         * @param  eid  The EID of the Entity to add.
         * @param  Mask  The mask to add to the Entity.
         */
        void addMask(EID, Mask);

        /**
         * @brief  Get the Mask value of an Entity.
         * 
         * @param  The EID of the Entity.
         * @return  The current Mask of the Entity.
         */
        Mask getMask(EID);

        /**
         * @brief Removes the bits in the Mask from the entity's Mask.
         * 
         * @param  eid  The EID of the Entity.
         * @param  mask  The mask to remove from the Entity's Mask.
         */
        void removeMask(EID, Mask);

        /**
         * @brief Get all Entities.
         *
         * @return The address of the internal Entity array.
         */
        Entity *getEntities();
    private:
        Entity entities[ECS_MAX_ENTITIES];
        EID nextEntity;

        void incrementNextEntity();
    };

} // end namespace Gamenge

#endif