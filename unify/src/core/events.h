#pragma once
#include "pch/un2pch.h"
#include "log.h"

namespace unify::core {

    enum class EventType {
        None,
        WindowClose, WindowResize, WindowMove, WindowFocus, WindowUnfocus,
        MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
        KeyPressed, KeyReleased
    };

    class Event {
        friend class WindowManager;
        friend class EventManager;
    public:
        Event(EventType type, std::function<void()> callbackFunc) : m_Type(type), m_CallbackFunc(callbackFunc) {};
        ~Event() = default;

        static void CreateEvent(EventType type, std::function<void()> callbackFunc);

    private:
        std::function<void()> m_CallbackFunc;
        bool m_IsHandled = false;
        EventType m_Type;
    };

    class EventManager {
        friend class Event;
        friend class Engine;
        friend class WindowManager;
    public:
        static EventManager& GetInstance();

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;

    private:
        EventManager() = default;
        ~EventManager() = default;

        static bool Initialize();
        static void Shutdown();
        static bool AddEventToQueue(std::shared_ptr<Event> event);
        static bool ProccessEventQueue();
    };

}