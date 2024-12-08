#include "pch/un2pch.h"
#include "core.h"
#include "log.h"
#include "logger.h"
#include "window.h"
#include "events.h"

namespace unify2::core {

    static Engine* m_Instance = NULL;
    static bool isRunning = false;

    Engine& Engine::GetInstance() { return *m_Instance; }

    void Engine::Initialize() {

        if (m_Instance == NULL) {
            m_Instance = new Engine();
            isRunning = true;
        }

        // Initialize Managers
        LogManager::Initialize();
        LOG_TRACE("Log Manager Initialized...");
        EventManager::Initialize();
        LOG_TRACE("Event Manager Initialized...");
        WindowManager::Initialize();
        LOG_TRACE("Window Manager Initialized...");

        Run();

    }


    void Engine::Run() {

        // Start main loop aka update
        while (isRunning) {
            WindowManager::Update();
            EventManager::ProccessEventQueue();
        }
    }

    void Engine::Shutdown() {
        isRunning = false;
        // Shutdown Managers
        LOG_TRACE("Shutting down Window Manager...");
        WindowManager::Shutdown();
        LOG_TRACE("Shutting down Event Manager...");
        EventManager::Shutdown();
        LOG_TRACE("Shutting down Log Manager...");
        LogManager::Shutdown();

        // delete instance pointer
        delete m_Instance;
        m_Instance = NULL;
    }

}