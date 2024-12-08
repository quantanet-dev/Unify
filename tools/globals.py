import os, sys, platform

# -- DO NOT CHANGE THESE VARIABLES
PLATFORM = sys.platform
ARCHITECTURE = platform.machine()
BASE_PATH = os.getcwd()
TOOLSET_VERSION_MAJOR = 2
TOOLSET_VERSION_MINOR = 1

# -- YOU MAY CHANGE THESE VARIABLES TO FIT YOUR PROJECT LAYOUT
ENGINE_NAME = "unify2"
PROJECT_NAME = "unifyeditor2"
BUILD_CONFIG = "Debug" # Options: Debug, Release
MSBUILD_PATH = "C:\\\\Program Files\\\\Microsoft Visual Studio\\\\2022\\\\Community\\\\MSBuild\\\\Current\\\\Bin\\\\MSBuild.exe"
TOOLS_DIR = "tools"

# -- DO NOT CHANGE THESE UNLESS YOU KNOW WHAT YOU ARE DOING!!!
PLATFORM_BUILD_CONFIG = "{}-{}-{}".format(BUILD_CONFIG, PLATFORM, ARCHITECTURE)
EXECUTABLE_PATH = "{}/bin/{}/{}".format(BASE_PATH, PLATFORM_BUILD_CONFIG, PROJECT_NAME)
LIB_PATH = "{}/bin/{}/{}".format(BASE_PATH, PLATFORM_BUILD_CONFIG, ENGINE_NAME)

if "microsoft" in platform.platform().lower():
    PLATFORM = "windows"

if "darwin" in PLATFORM.lower():
    ARCHITECTURE = "universal"

def IsWindows():
    return PLATFORM == "windows"

def IsLinux():
    return PLATFORM == "linux"

def IsMacos():
    return PLATFORM == "darwin"