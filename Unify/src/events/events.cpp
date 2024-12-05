#include <events/events.h>

namespace Unify::events
{
    void Event::ProccessEvent(Event event)
    {
        EventType eventType = this->GetEventType();
        std::cout << (int)eventType << "\n";
    };
}