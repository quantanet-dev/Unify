workspace "unify2"
    startproject "unifyeditor2"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

project "unifyeditor2"
    location "unifyeditor2"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    flags {
        "FatalWarnings"
    }