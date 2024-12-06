import os
import sys
import platform

ENGINE_NAME = "unify2"
PROJECT_NAME = "unifyeditor2"
VERSION_MAJOR = 2
VERSION_MINOR = 0
CONFIG = "Debug" # Options: Debug, Release
PLATFORM = sys.platform
PLATFORM2 = platform.platform()
ARCHITECTURE = platform.machine()

if "microsoft" in PLATFORM2.lower():
    PLATFORM = "windows"

CONFIG = "{}-{}-{}".format(CONFIG, PLATFORM, ARCHITECTURE)

TOOLS_DIR = "tools"
EXECUTABLE_PATH = "{}/bin/{}/{}".format(os.getcwd(), CONFIG, PROJECT_NAME)

def IsWindows():
    return PLATFORM == "windows"

def IsLinux():
    return PLATFORM == "linux"

def IsMacos():
    return PLATFORM == "darwin"