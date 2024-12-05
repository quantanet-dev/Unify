#pragma once

#include <unpch.h>
#include <core/core.h>

namespace Unify::events
{

    enum class EventType
    {
        None = 0,
        WindowResize,
        WindowClose,
        WindowMove,
        KeyPressed,
        KeyReleased,
        ButtonPressed,
        ButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    class Event
    {
    public:
        virtual ~Event() {};
        inline EventType GetEventType() const { return m_EventType; }

    protected:
        Event(EventType type) : m_EventType(type)
        {
            ProccessEvent(*this);
        };
        EventType m_EventType;
        bool m_IsHandled = false;

    private:
        void ProccessEvent(Event event);
    };

}
