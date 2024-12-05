#include <core/core.h>
#include <managers/managers.h>

namespace Unify::managers
{

    void UnifyWindowManager::Initialize(int width, int height, const char *title)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Unable to initialize GLFW instance!");
        }
        else
        {
            m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
            if (!m_Window)
            {
                throw std::runtime_error("Unable to initialize window!");
            }
            glfwMakeContextCurrent(m_Window);
        }
    };
    void UnifyWindowManager::Update()
    {
        switch (glfwWindowShouldClose(m_Window))
        {
        case GLFW_FALSE:
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
            break;
        case GLFW_TRUE:
            Unify::UnifyEngine::GetInstance().Shutdown();
        default:
            break;
        }
    };
    void UnifyWindowManager::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    };
}