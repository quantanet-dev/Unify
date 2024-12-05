#pragma once

#include <unpch.h>

namespace Unify
{
    class UnifyApplication
    {
    public:
        virtual ~UnifyApplication() {};
        void Run();
    };

    class UnifyEngine
    {
    public:
        static UnifyEngine &GetInstance()
        {
            static UnifyEngine instance;
            return instance;
        }
        void Initialize();
        void Update();
        void Shutdown();

        bool m_Initialized = false;
    private:
        // singleton
        UnifyEngine() = default;
        ~UnifyEngine() = default;
        UnifyEngine(const UnifyEngine &) = delete;
        UnifyEngine &operator=(const UnifyEngine &) = delete;
    };

}
