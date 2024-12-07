workspace "unify2"
    architecture "x64"
    startproject "unifyeditor2"
    buildoptions {
		"/MTd"
	}

    configurations {
        "Debug-windows-x86_64",
        "Debug-windows-arm64",
        "Release-windows-x86_64",
        "Release-windows-arm64",
        "Debug-linux-x86_64",
        "Debug-linux-arm64",
        "Release-linux-x86_64",
        "Release-linux-arm64",
        "Debug-darwin-x86_64",
        "Debug-darwin-arm64",
        "Release-darwin-x86_64",
        "Release-darwin-arm64",
    }

outputDir = "%{cfg.buildcfg}"

include "unify2/vendor/glfw"

project "unify2"
    location "unify2"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"
    characterset ("Unicode")
    links {
        "glfw"
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
            "UNIFY2_PLATFORM_WINDOWS",
            "UNIFY2_BUILD_DLL"
        }
    
    filter {"system:macosx", "configurations:*"}
        defines {
            "UNIFY2_PLATFORM_MACOS"
        }

    filter {"system:linux", "configurations:*"}
        defines {
            "UNIFY2_PLATFORM_LINUX"
        }

    filter {"system:*", "configurations:Debug-windows-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-windows-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-windows-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-windows-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-linux-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-linux-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-linux-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-linux-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-darwin-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-darwin-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-darwin-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-darwin-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }


project "unifyeditor2"
    location "unifyeditor2"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    links "unify2"
    characterset ("Unicode")

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs{
        "unify2/src"
    }

    flags {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"
        postbuildcommands {
            ("{COPYFILE} %[bin/%{!outputDir}/unify2/unify2.dll] %[bin/%{!outputDir}/unifyeditor2/unify2.dll]")
        }
        buildoptions {
            "/utf-8"
        }
        defines {
            "UNIFY2_PLATFORM_WINDOWS"
        }
    
    filter {"system:macosx", "configurations:*"}
        defines {
            "UNIFY2_PLATFORM_MACOS"
        }

    filter {"system:linux", "configurations:*"}
        defines {
            "UNIFY2_PLATFORM_LINUX"
        }

    filter {"system:*", "configurations:Debug-windows-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-windows-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-windows-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-windows-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-linux-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-linux-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-linux-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-linux-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Debug-darwin-x86_64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-darwin-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-darwin-x86_64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-darwin-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }