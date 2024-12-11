#include "pch/un2pch.h"
#include "events.h"

namespace unify::core {

    std::map<EventType, std::string> EventTypeToString = {
    {EventType::None, "None"},
    {EventType::WindowClose, "WindowClose"},
    {EventType::WindowResize, "WindowResize"},
    {EventType::WindowMove, "WindowMove"},
    {EventType::WindowFocus, "WindowFocus"},
    {EventType::WindowUnfocus, "WindowUnfocus"},
    {EventType::MouseMoved, "MouseMoved"},
    {EventType::MouseScrolled, "MouseScrolled"},
    {EventType::MouseButtonPressed, "MouseButtonPressed"},
    {EventType::MouseButtonReleased, "MouseButtonReleased"},
    {EventType::KeyPressed, "KeyPressed"},
    {EventType::KeyReleased, "KeyReleased"}
    };

    void Event::CreateNewEvent(EventType type, std::function<void()> callbackFunc) {
        EventManager::AddEventToQueue(std::make_shared<Event>(type, callbackFunc));
    }

   
    EventManager& EventManager::GetInstance() {
        static EventManager* m_Instance = new EventManager;
        return *m_Instance;
    }

    static std::vector<std::shared_ptr<Event>> m_EventsQueue;

    void EventManager::Initialize() {}

    void EventManager::Shutdown() {}

    std::string GetEventTypeToString(EventType type) {
        auto it = EventTypeToString.find(type);
        if (it != EventTypeToString.end()) {
            return it->second;
        }
        else {
            return "Could not map the event to a string\n";
        }
    };

    void EventManager::AddEventToQueue(std::shared_ptr<Event> event) {
        /* std::string str = GetEventTypeToString(event->m_Type);
         LOG_TRACE(str);*/
        m_EventsQueue.push_back(event);
    }

    void EventManager::Update() {
        for (std::shared_ptr<Event> event : m_EventsQueue) {
            event->m_CallbackFunc();
            event->m_IsHandled = true;
        }
        m_EventsQueue.clear();
    }

}