#pragma once

#include "core.h"

namespace unify::core {

    enum class EventType {
        None,
        WindowClose, WindowResize, WindowMove, WindowFocus, WindowUnfocus,
        MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
        KeyPressed, KeyReleased
    };

    class Event {
    public:
        Event(EventType type, std::function<void()> callbackFunc) : m_Type(type), m_CallbackFunc(callbackFunc) {};
        ~Event() = default;

        static void CreateNewEvent(EventType type, std::function<void()> callbackFunc);

        std::function<void()> m_CallbackFunc;
        bool m_IsHandled = false;
        EventType m_Type;
    };

    class EventManager : IManager {
        friend class Engine;
    public:
        static EventManager& GetInstance();

        void Initialize();
        void Update();
        void Shutdown();
        static void AddEventToQueue(std::shared_ptr<Event> event);

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;

    private:
        EventManager() = default;
        ~EventManager() = default;
    };

}