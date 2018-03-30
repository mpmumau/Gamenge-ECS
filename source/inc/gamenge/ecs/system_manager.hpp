#ifndef GAMENGE_ECS_SYSTEM_MANAGER_H
#define GAMENGE_ECS_SYSTEM_MANAGER_H

#include <forward_list>

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/system.hpp>
#include <gamenge/ecs/entity_manager.hpp>
#include <gamenge/ecs/component_manager.hpp>

using namespace Gamenge;

namespace Gamenge {

    class SystemManager {
    public:
        ~SystemManager();
        void addSystem(System *);
        void removeSystem(Mask);
        void tick(Nanos, EntityManager *, ComponentManager *);
        unsigned int getNumSystems();
        void destroy();
    private:
        std::forward_list<System *> systems;
        static bool sortSystems(System* &, System* &);
    };

}

#endif