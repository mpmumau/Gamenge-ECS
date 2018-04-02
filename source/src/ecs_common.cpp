#include <gamenge/ecs/ecs_common.hpp>

using namespace Gamenge;

bool MaskUtils::matches(Mask haystack, Mask needle)
{
    return (needle & haystack) == needle;
}

bool MaskUtils::matchesAny(Mask needle, Mask haystack)
{
    return (needle & haystack) != Mask(0x00);
}

Entity::Entity()
{
    mask = Mask(0x00);
    enabled = false;
}

Entity::Entity(Mask mask, bool enabled)
{
    this->mask = mask;
    this->enabled = enabled;
}

Message::Message(EID target, MessageType type)
{
    this->target = target;
    this->type = type;
}

void MessagingComponent::receiveMessage(Message *message)
{
    messages.push_front(message);
}