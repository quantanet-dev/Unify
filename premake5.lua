workspace "unify"
    startproject "unifyeditor"

    configurations {
        "Debug-windows-x86_64",
        "Debug-windows-arm64",
        "Release-windows-x86_64",
        "Release-windows-arm64",
        "Debug-linux-x86_64",
        "Debug-linux-arm64",
        "Release-linux-x86_64",
        "Release-linux-arm64",
        "Debug-darwin-universal",
        "Release-darwin-universal",
    }

    filter {"system:windows"}
        buildoptions {
            "/MTd"
        }

outputDir = "%{cfg.buildcfg}"

include "unify/vendor/glfw"
include "unify/vendor/glad"

project "unify"
    location "unify"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"
    characterset ("Unicode")
    links {
        "glfw",
        "glad"
    }

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-obj/" .. outputDir .. "/%{prj.name}")

    pchheader "pch/un2pch.h"
    pchsource "%{prj.name}/src/pch/un2pch.cpp"
    
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/glfw/include"
        "%{prj.name}/vendor/glad/include"
    }
    
    flags {
        "FatalWarnings"
    }
    
    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        buildoptions {
            "/utf-8"
        }
    
        defines {
            "UNIFY_PLATFORM_WINDOWS",
            "UNIFY_BUILD_DLL"
        }
    
    filter {"system:macosx", "configurations:*"}
        defines {
            "UNIFY_PLATFORM_MACOS"
        }
        links {
            "/System/Library/Frameworks/Cocoa.framework",
            "/System/Library/Frameworks/OpenGL.framework",
            "/System/Library/Frameworks/IOKit.framework",
            "/System/Library/Frameworks/CoreVideo.framework",
            "/System/Library/Frameworks/QuartzCore.framework",
        }

    filter {"system:linux", "configurations:*"}
        defines {
            "UNIFY_PLATFORM_LINUX"
        }

    filter {"system:*", "configurations:Debug-windows-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-windows-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-windows-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-windows-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-linux-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-linux-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-linux-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-linux-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-darwin-universal"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_UNIVERSAL"
        }

    filter {"system:*", "configurations:Release-darwin-universal"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_UNIVERSAL"
        }

project "unifyeditor"
    location "unifyeditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    links "unify"
    characterset ("Unicode")

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs{
        "unify/src"
    }

    flags {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"
        postbuildcommands {
            ("{COPYFILE} %[bin/%{!outputDir}/unify/unify.dll] %[bin/%{!outputDir}/unifyeditor/unify.dll]")
        }
        buildoptions {
            "/utf-8"
        }
        defines {
            "UNIFY_PLATFORM_WINDOWS"
        }
    
    filter {"system:macosx", "configurations:*"}
        defines {
            "UNIFY_PLATFORM_MACOS"
        }

    filter {"system:linux", "configurations:*"}
        defines {
            "UNIFY_PLATFORM_LINUX"
        }

    filter {"system:*", "configurations:Debug-windows-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-windows-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-windows-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-windows-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-linux-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-linux-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-linux-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-linux-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-darwin-universal"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY_CONFIG_DEBUG",
            "UNIFY_ARCH_UNIVERSAL"
        }

    filter {"system:*", "configurations:Release-darwin-universal"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY_CONFIG_RELEASE",
            "UNIFY_ARCH_UNIVERSAL"
        }