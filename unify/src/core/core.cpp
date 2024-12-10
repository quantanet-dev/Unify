#include "pch/un2pch.h"
#include "core.h"
#include "log.h"
#include "logger.h"
#include "window.h"
#include "events.h"

namespace unify::core {

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
        LOG_INFO("Log Manager Initialized...");
        EventManager::Initialize();
        LOG_INFO("Event Manager Initialized...");
        WindowManager::Initialize();
        LOG_INFO("Window Manager Initialized...");
       /* RenderManager::Initialize();
        LOG_INFO("Render Manager Initialized...");*/

        Run();

    }


    void Engine::Run() {

        // Start main loop aka update
        while (isRunning) {
            EventManager::Update();
            WindowManager::Update();
           /* RenderManager::Update();*/
        }
    }

    void Engine::Shutdown() {
        isRunning = false;
        // Shutdown Managers
      /*  LOG_INFO("Shutting down Render Manager...");
        RenderManager::Shutdown();*/
        LOG_INFO("Shutting down Window Manager...");
        WindowManager::Shutdown();
        LOG_INFO("Shutting down Event Manager...");
        EventManager::Shutdown();
        LOG_INFO("Shutting down Log Manager...");
        LogManager::Shutdown();

        // delete instance pointer
        delete m_Instance;
        m_Instance = NULL;
    }

}