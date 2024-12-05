#pragma once

#include <events.h>

namespace Unify::events
{

    class MouseEvent : public Event
    {
    public:
        ~MouseEvent() {};
        inline float GetMousePosX() const { return m_MouseX; }
        inline float GetMousePosY() const { return m_MouseY; }
        inline float GetMouseScrollX() const { return m_ScrollX; }
        inline float GetMouseScrollY() const { return m_ScrollY; }

    protected:
        MouseEvent(EventType type, float mouseX, float mouseY, float scrollX, float scrollY) : Event(type), m_MouseX(mouseX), m_MouseY(mouseY), m_ScrollX(scrollX), m_ScrollY(scrollY) {};

        float m_MouseX;
        float m_MouseY;
        float m_ScrollX;
        float m_ScrollY;
    };

    class MouseMoveEvent : public MouseEvent
    {
    public:
        MouseMoveEvent(float mouseX, float mouseY) : MouseEvent(EventType::MouseMoved, mouseX, mouseY, NULL, NULL) {};
        ~MouseMoveEvent() {};
    };

    class MouseScrollEvent : public MouseEvent
    {
    public:
        MouseScrollEvent(float scrollX, float scrollY) : MouseEvent(EventType::MouseScrolled, NULL, NULL, scrollX, scrollY) {};
        ~MouseScrollEvent() {};
    };
}