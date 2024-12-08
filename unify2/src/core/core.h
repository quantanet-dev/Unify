#pragma once

namespace unify2::core {

    class Engine {
    public:
        static Engine& GetInstance();

        static void Initialize();
        static void Shutdown();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

    private:
        Engine() = default;
        ~Engine() = default;
    };

}