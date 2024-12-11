#include "pch/un2pch.h"
#include "core.h"
#include "logger.h"
#include "events.h"
#include "window.h"
#include "renderer.h"

namespace unify::core {

    static bool isRunning = false;

    Engine& Engine::GetInstance() { 
        static Engine* m_Instance = new Engine;
        return *m_Instance;
    }

    void Engine::AddManager(IManager& manager) {
        m_Managers.emplace_back(manager);
    }

    void Engine::Initialize() {

       // Add managers to m_Managers vector

        AddManager(LogManager::GetInstance());

        AddManager(EventManager::GetInstance());

        AddManager(WindowManager::GetInstance());

       // Set isRunning flag to true;
        isRunning = true;

       // Initialize all of the managers within the engine class
        for (IManager& manager : m_Managers) {
            manager.Initialize();
        }

        Run();
    }

    void Engine::Run() {

        // If running flag set to true, update all of the managers
        while (isRunning) {
            for (IManager& manager : m_Managers) {
                manager.Update();
            }
        }
 
    }

    void Engine::Shutdown() {
        isRunning = false;
        // loop through the managers vector in reverse and shutdown all of the managers
        for (auto manager = m_Managers.rbegin(); manager != m_Managers.rend(); manager++) {
            manager->get().Shutdown();
        }

    }

}