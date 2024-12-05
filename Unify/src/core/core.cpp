#include <core/core.h>
#include <managers/managers.h>

namespace Unify
{

    void UnifyApplication::Run()
    {
        UnifyEngine::GetInstance().Initialize();
        while (UnifyEngine::GetInstance().m_Initialized == true)
        {
            UnifyEngine::GetInstance().Update();
        };
    };

    void UnifyEngine::Initialize()
    {
        managers::UnifyLogManager::GetInstance().Initialize();
        managers::UnifyEventManager::GetInstance().Initialize();
        managers::UnifyWindowManager::GetInstance().Initialize(1280, 720, "Hello Unify!");

        // Set initialization flag to true.
        m_Initialized = true;
    }

    void UnifyEngine::Update()
    {
        managers::UnifyLogManager::GetInstance().Update();
        managers::UnifyEventManager::GetInstance().Update();
        managers::UnifyWindowManager::GetInstance().Update();
    }

    void UnifyEngine::Shutdown()
    {
        managers::UnifyWindowManager::GetInstance().Shutdown();
        managers::UnifyEventManager::GetInstance().Shutdown();
        managers::UnifyLogManager::GetInstance().Shutdown();

        // Set initialization flag to false.s
        m_Initialized = false;
    };
}