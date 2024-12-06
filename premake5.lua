workspace "unify2"
    architecture "x64"
    startproject "unifyeditor2"

    configurations {
        "Debug-x64",
        "Debug-arm64",
        "Release-x64",
        "Release-arm64",
    }

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "unify2"
    location "unify2"
    kind "SharedLib"
    language "C++"
    cppdialect "C++23"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "%{prj.name}/src"
    }

    flags {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines {
            "UNIFY2_PLATFORM_WINDOWS",
            "UNIFY2_BUILD_DLL"
        }
    
    filter {"system:macosx", "configurations:*"}
        xcodebuildsettings{
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }

        defines {
            "UNIFY2_PLATFORM_MACOS"
        }

    filter {"system:linux", "configurations:*"}
        defines {
            "UNIFY2_PLATFORM_LINUX"
        }

    filter {"system:*", "configurations:Debug-x64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-x64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-arm64"}
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

    -- postbuildcommands {
    --     ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/unifyeditor2")
    -- }

    postbuildcommands {
        ("{COPYFILE} %[bin/%{!outputDir}/unify2/unify2.dll] %[bin/%{!outputDir}/unifyeditor2/unify2.dll]")
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines {
            "UNIFY2_PLATFORM_WINDOWS",
        }
    
    filter {"system:macosx", "configurations:*"}
        xcodebuildsettings{
            ["MACOSX_DEPLOYMENT_TARGET"] = "10.15",
            ["UseModernBuildSystem"] = "NO"
        }

        defines {
            "UNIFY2_PLATFORM_MACOS"
        }

    filter {"system:linux", "configurations:*"}
        defines {
            "UNIFY2_PLATFORM_LINUX"
        }

    filter {"system:*", "configurations:Debug-x64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Debug-arm64"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG",
            "UNIFY2_ARCH_ARM64"
        }

    filter {"system:*", "configurations:Release-x64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_X64"
        }

    filter {"system:*", "configurations:Release-arm64"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE",
            "UNIFY2_ARCH_ARM64"
        }