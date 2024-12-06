workspaceDirectory = "solution-files/"

workspace "unify2"
    location(workspaceDirectory)
    startproject "unifyeditor2"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

targetDirectory = "bin/%{cfg.buildcfg}/%{prj.name}"
objectDirectory = "bin-obj/%{cfg.buildcfg}/%{prj.name}"

projectDirectory = "project-files/%{prj.name}"

project "unify2"
    location(projectDirectory)
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "On"

    targetdir(targetDirectory)
    objdir(objectDirectory)

    files {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs{
        "%{prj.name}/include/unify2"
    }

    flags {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
        systemversion "latest"

        defines {
            "UNIFY2_PLATFORM_WINDOWS"
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

    filter {"system:*", "configurations:Debug"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG"
        }

    filter {"system:*", "configurations:Release"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE"
        }

project "unifyeditor2"
    location(projectDirectory)
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "On"
    links "unify2"

    targetdir(targetDirectory)
    objdir(objectDirectory)

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs{
        "unify2/include",
    }

    flags {
        "FatalWarnings"
    }

    filter {"system:windows", "configurations:*"}
    systemversion "latest"

    defines {
        "UNIFY2_PLATFORM_WINDOWS"
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

    filter {"system:*", "configurations:Debug"}
        runtime "Debug"
        symbols "On"
        defines {
            "UNIFY2_CONFIG_DEBUG"
        }

    filter {"system:*", "configurations:Release"}
        runtime "Release"
        symbols "Off"
        optimize "On"
        defines {
            "UNIFY2_CONFIG_RELEASE"
        }