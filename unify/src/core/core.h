#pragma once

namespace unify::core {

    struct IManager {
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Shutdown() = 0;
    };

    struct IEngine {
        virtual void Initialize() = 0;
        virtual void Run() = 0;
        virtual void Shutdown() = 0;
        virtual void AddManager(IManager& manager) = 0;
    };

    class Engine : IEngine {
    public:
        static Engine& GetInstance();

        void Initialize() override;
        void Run() override;
        void Shutdown() override;
        void AddManager(IManager& manager) override;

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

    private:
        Engine() = default;
        ~Engine() = default;

    private:
        std::vector<std::reference_wrapper<IManager>> m_Managers;
    };

}