#pragma once

#include <events.h>

namespace Unify::events
{

    class KeyEvent : public Event
    {
    public:
        ~KeyEvent() {};
        inline int GetKeyCode() const { return m_KeyCode; }

    protected:
        KeyEvent(EventType type, int keyCode, int repeatCount) : Event(type), m_KeyCode(keyCode), m_RepeatCount(repeatCount) {};
        int m_KeyCode;
        int m_RepeatCount;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(EventType::KeyPressed, keyCode, repeatCount) {};
        ~KeyPressedEvent();
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode) : KeyEvent(EventType::KeyReleased, keyCode, NULL) {};
        ~KeyReleasedEvent();
    };

}