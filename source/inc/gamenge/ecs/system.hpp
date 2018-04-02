#ifndef GAMENGE_ECS_SYSTEM_H
#define GAMENGE_ECS_SYSTEM_H

#include <gamenge/common/common.hpp>
#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

namespace Gamenge {

    /**
     * @brief Base class from which to derive ECS Systems.
     */
    class System {
    public:
        /**
         * @brief Construct a System.
         * 
         * @param  mask  The Mask to use for the System's ComponentBundle retrieval.
         * @param  sortOrder  The order in which the System will be called with respect to other Systems.
         */
        System(Mask, unsigned short);

        /**
         * @brief Construct a System, and specify whether or not to include Messaging.
         * 
         * @param  mask  The Mask to use for the System's ComponentBundle retrieval.
         * @param  sortOrder  The order in which the System will be called with respect to other Systems.
         * @param  messaging  Whether or not the System will retrieve MessagingComponent objects for Entities.
         */
        System(Mask, unsigned short, bool);

        /**
         * @brief Default destructor.
         */
        virtual ~System() {};
        
        /**
         * @brief  Get the Mask value of the System.
         *
         * @return  The Mask value of the System.
         */
        Mask getMask();

        /**
         * @brief  Get the sort order value of the System.
         *
         * @return  A numerical sort order value for the System.
         */
        unsigned short getSortOrder();

        /**
         * @brief Determine whether or not a given System uses Messaging.
         *
         * @return  A boolean representing whether or not the System uses Messaging.
         */
        bool usesMessaging();

        /**
         * @brief The primary tick function for the system; must be overridden by children Systems.
         * 
         * @param  delta  The time in nanoseconds to simulate during the tick.
         * @param  eid  The EID value of the Entity to be acted upon.
         * @param  componentBundle  A ComponentBundle value containing pointers to generic Component objects, 
         * matched to the System's Mask value.
         */
        virtual void tick(Nanos, EID, ComponentBundle) = 0;
    protected:
        Mask mask;
        bool messaging;
        unsigned short sortOrder;
    };

}

#endif