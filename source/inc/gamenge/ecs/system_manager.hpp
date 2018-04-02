#ifndef GAMENGE_ECS_SYSTEM_MANAGER_H
#define GAMENGE_ECS_SYSTEM_MANAGER_H

#include <forward_list>

#include <gamenge/ecs/system.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>

namespace Gamenge {
    /**
     * @brief A class for handling System operations and data.
     */
    class SystemManager {
    public:
        /**
         * @brief Destroy the SystemManager and release its resources.
         */
        ~SystemManager();

        /**
         * @brief  Add a System to the SystemManager.
         * 
         * @param system A pointer to the System to add.
         */
        void addSystem(System *);

        /**
         * @brief  Remove a System.
         * 
         * @param  mask  The Mask of the System to remove.
         */
        void removeSystem(System *);

        /**
         * @brief Primary tick function for the SystemManager; iterates through all Systems and calls their tick functions.
         * 
         * @param delta  The time in nanoseconds to simulate in the tick.
         * @param entityManager  A pointer to the EntityManager class from which to take Entity data.
         * @param componentManager  A pointer to the ComponentManager class from which to take Component data.
         */
        void tick(Nanos, EntityManager *, ComponentManager *);

        /**
         * @brief Get the number of Systems added to the SystemManager.
         * @return  The numerical value of the number of Systems in the SystemManager.
         */
        unsigned int getNumSystems();

        /**
         * @brief  Destroy the SystemManager and release its resources.
         */
        void destroy();
    private:
        std::forward_list<System *> systems;
        static bool sortSystems(System* &, System* &);
    };

} // end namespace Gamenge

#endif