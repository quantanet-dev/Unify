#include "engine.h"
#include <iostream>

namespace unify2
{
        void GetInfo()
        {
#ifdef UNIFY2_CONFIG_DEBUG
                std::cout << "Configuration: DEBUG" << std::endl;
#endif
#ifdef UNIFY2_CONFIG_RELEASE
                std::cout << "Configuration: RELEASE" << std::endl;
#endif
#ifdef UNIFY2_PLATFORM_WINDOWS
                std::cout << "Platform: WINDOWS" << std::endl;
#endif
#ifdef UNIFY2_PLATFORM_MACOS
                std::cout << "Platform : MACOS" << std::endl;
#endif
#ifdef UNIFY2_PLATFORM_LINUX
                std::cout << "Platform : LINUX" << std::endl;
#endif
        }
}