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

project "unifyeditor2"
    location(projectDirectory)
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir(targetDirectory)
    objdir(objectDirectory)

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    flags {
        "FatalWarnings"
    }