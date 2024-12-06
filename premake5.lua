workspace "unify2"
    architecture "x64"
    startproject "unifyeditor2"

    configurations {
        "Debug",
        "Release"
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