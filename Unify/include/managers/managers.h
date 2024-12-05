#pragma once

#include <unpch.h>
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Unify::managers
{

    class UnifyLogManager
    {
    public:
        static UnifyLogManager &GetInstance()
        {
            static UnifyLogManager instance;
            return instance;
        }

        void Initialize();
        void Update();
        void Shutdown();

    private:
        // singleton
        UnifyLogManager() = default;
        ~UnifyLogManager() = default;
        UnifyLogManager(const UnifyLogManager &) = delete;
        UnifyLogManager &operator=(const UnifyLogManager &) = delete;
    };

    class UnifyEventManager
    {
    public:
        static UnifyEventManager &GetInstance()
        {
            static UnifyEventManager instance;
            return instance;
        }

        void Initialize() {};
        void Update() {};
        void Shutdown() {};

    private:
        UnifyEventManager() = default;
        ~UnifyEventManager() = default;
        UnifyEventManager(const UnifyEventManager &) = delete;
        UnifyEventManager &operator=(const UnifyEventManager &) = delete;
    };

    class UnifyWindowManager
    {
    public:
        static UnifyWindowManager &GetInstance()
        {
            static UnifyWindowManager instance;
            return instance;
        }

        void Initialize(int width, int height, const char *title);
        void Update();
        void Shutdown();

    private:
        // data
        GLFWwindow *m_Window = NULL;

        // singleton
        UnifyWindowManager() = default;
        ~UnifyWindowManager() = default;
        UnifyWindowManager(const UnifyWindowManager &) = delete;
        UnifyWindowManager &operator=(const UnifyWindowManager &) = delete;
    };
}