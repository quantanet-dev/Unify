#include "pch/un2pch.h"
#include "events.h"

namespace unify2::core {

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

    void Event::CreateEvent(EventType type, std::function<void()> callbackFunc) {
        EventManager::AddEventToQueue(std::make_shared<Event>(type, callbackFunc));
    }

    static EventManager* m_Instance = NULL;
    EventManager& EventManager::GetInstance() { return *m_Instance; }

    static std::vector<std::shared_ptr<Event>> m_EventsQueue;

    bool EventManager::Initialize() {

        bool isInitialized = true;

        if (m_Instance == NULL) {
            m_Instance = new EventManager();
        }

        return isInitialized;
    }

    void EventManager::Shutdown() {

        delete m_Instance;
        m_Instance = NULL;

    }

    std::string GetEventTypeToString(EventType type) {
        auto it = EventTypeToString.find(type);
        if (it != EventTypeToString.end()) {
            return it->second;
        }
        else {
            return "Could not map the event to a string\n";
        }
    };

    bool EventManager::AddEventToQueue(std::shared_ptr<Event> event) {
       /* std::string str = GetEventTypeToString(event->m_Type);
        LOG_TRACE(str);*/
        m_EventsQueue.push_back(event);
        return true;
    }

    bool EventManager::ProccessEventQueue() {
         for (std::shared_ptr<Event> event : m_EventsQueue) {
             event->m_CallbackFunc();
             event->m_IsHandled = true;
         }
         m_EventsQueue.clear();
         return true;
    }

}