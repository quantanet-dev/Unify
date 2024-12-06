#pragma once

#ifdef UNIFY2_PLATFORM_WINDOWS
#ifdef  UNIFY2_BUILD_DLL
#define UNIFY2_API __declspec(dllexport) // MSVC
#else
#define UNIFY2_API __declspec(dllimport)
#endif
#elif UNIFY2_PLATFORM_LINUX
#ifdef UNIFY2_BUILD_DLL
#define UNIFY2_API __attribute__((visibility("default"))) //GCC
#endif
#else 
#define UNIFY2_API
#endif

