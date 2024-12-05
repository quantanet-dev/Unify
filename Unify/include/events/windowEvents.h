#pragma once

#include <events/events.h>

namespace Unify::events
{

    class WindowEvent : public Event
    {
    public:
        ~WindowEvent() {};

    protected:
        WindowEvent(EventType type) : Event(type) {};
    };

    class WindowResizeEvent : public WindowEvent
    {
    public:
        WindowResizeEvent(int width, int height) : WindowEvent(EventType::WindowResize), m_Width(width), m_Height(height) {};
        ~WindowResizeEvent() {};

    private:
        int m_Width;
        int m_Height;
    };

    class WindowCloseEvent : public WindowEvent
    {
    public:
        WindowCloseEvent() : WindowEvent(EventType::WindowClose) {};
        ~WindowCloseEvent() {};
    };

    class WindowMoveEvent : public WindowEvent
    {
    public:
        WindowMoveEvent() : WindowEvent(EventType::WindowMove) {};
        ~WindowMoveEvent() {};
    };

}