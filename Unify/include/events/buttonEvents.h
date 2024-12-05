#pragma once

#include <events.h>

namespace Unify::events
{

    class ButtonEvent : public Event
    {
    public:
        ~ButtonEvent() {};
        inline int GetButton() const { return m_Button; }

    protected:
        ButtonEvent(EventType type, int button) : Event(type), m_Button(button) {};
        int m_Button;
    };

    class ButtonPressedEvent : public ButtonEvent
    {
    public:
        ButtonPressedEvent(int button) : ButtonEvent(EventType::ButtonPressed, button) {};
        ~ButtonPressedEvent() {};
    };

    class ButtonReleasedEvent : public ButtonEvent
    {
    public:
        ButtonReleasedEvent(int button) : ButtonEvent(EventType::ButtonReleased, button) {};
        ~ButtonReleasedEvent() {};
    };

}