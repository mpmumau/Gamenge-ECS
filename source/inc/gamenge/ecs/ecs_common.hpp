#ifndef GAMENGE_ECS_COMMON_H
#define GAMENGE_ECS_COMMON_H

#include <bitset>
#include <unordered_map>
#include <forward_list>

#define ECS_MAX_ENTITIES 65536
#define ECS_MAX_COMPONENTS 128

namespace Gamenge {

    typedef unsigned long long Nanos;

    typedef std::bitset<ECS_MAX_COMPONENTS> Mask;

    typedef unsigned int EID;

    typedef struct Entity {
        Entity();
        Entity(Mask, bool);
        Mask mask;
        bool enabled;
    } Entity;

    typedef unsigned short MessageType;

    typedef struct Message {
        Message(EID, MessageType);
        virtual ~Message() {};
        EID target;
        MessageType type;
    } Message;
    
    typedef struct Component {
        virtual ~Component() {}
    } Component;

    typedef struct MessagingComponent : public Component {
        void receiveMessage(Message *);
        void deleteMessage(Message *);
        std::forward_list<Message *> messages;
    } MessagingComponent;

    typedef std::unordered_map<Mask, Component *> ComponentBundle;

    namespace MaskUtils {
        bool matches(Mask, Mask);
        bool matchesAny(Mask, Mask);
    }

} // end namespace Gamenge

#endif