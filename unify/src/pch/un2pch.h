// Unify2 Platform Macros

#ifdef UNIFY_PLATFORM_WINDOWS
#ifdef  UNIFY_BUILD_DLL
#define UNIFY_API __declspec(dllexport) // MSVC
#else
#define UNIFY_API __declspec(dllimport)
#endif
#elif UNIFY_PLATFORM_LINUX
#ifdef UNIFY_BUILD_DLL
#define UNIFY_API __attribute__((visibility("default"))) //GCC
#else 
#define UNIFY_API
#endif
#elif UNIFY_PLATFORM_MACOS 
#define UNIFY_API
#else
#define UNIFY_API
#endif

// Pre-compiled headers

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>