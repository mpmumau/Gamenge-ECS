#ifndef GAMENGE_ECS_COMMON_H
#define GAMENGE_ECS_COMMON_H

#include <map>
#include <forward_list>
#include <gamenge/common/common.hpp>

#define ECS_MAX_ENTITIES 65536

using namespace Gamenge;

namespace Gamenge {

    typedef unsigned long long int Mask;

    typedef unsigned int EID;

    typedef struct Entity {
        Mask mask;
        bool enabled;
    } Entity;
    
    typedef struct Component {
        virtual ~Component() {}
    } Component;

    typedef unsigned short MessageType;

    typedef struct Message {
        Message(EID, MessageType);
        virtual ~Message() {};
        EID target;
        MessageType type;
    } Message;

    typedef struct MessagingComponent : public Component {
        void receiveMessage(Message *);
        std::forward_list<Message *> messages;
    } MessagingComponent;

    typedef std::map<Mask, Component *> ComponentBundle;

    namespace MaskUtils {
        bool matches(Mask, Mask);
        bool matchesAny(Mask, Mask);
    }

} // end namespace Gamenge

#endif