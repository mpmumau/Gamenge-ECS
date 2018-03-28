#ifndef GAMENGE_ECS_ECS_DEF
#define GAMENGE_ECS_ECS_DEF

#define ECS_MAX_ENTITIES 65536

#include <map>

#include <gamenge/common/common.hpp>

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
    
    typedef std::map<Mask, Component *> ComponentBundle;
}

namespace Gamenge {
    namespace MaskUtils {
        bool matches(Mask, Mask);
        bool matchesAny(Mask, Mask);
    }
}

namespace Gamenge {
    class ECS {
    public:
        EID addEntity();
    private:
    };

} // end namespace Gamenge

#endif