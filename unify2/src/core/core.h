#pragma once

#include "application/application.h"

namespace unify2::core {

    class Engine {
        friend class unify2::Application;
        friend class WindowManager;
    public:
        static Engine& GetInstance();


        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

    private:
        Engine() = default;
        ~Engine() = default;

        static void Initialize();
        static void Run();
        static void Shutdown();
    };

}