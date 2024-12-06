import os
import sys
import platform

ENGINE_NAME = "unify2"
PROJECT_NAME = "unifyeditor2"
VERSION_MAJOR = 1
VERSION_MINOR = 0
CONFIG = "Debug"
PLATFORM = sys.platform
PLATFORM2 = platform.platform()
ARCHITECTURE = platform.machine()

if "microsoft" in PLATFORM2.lower():
    PLATFORM = "windows"


TOOLS_DIR = "tools"
EXECUTABLE_PATH = "{}/bin/{}-{}-{}/{}".format(os.getcwd(), CONFIG, PLATFORM, ARCHITECTURE, PROJECT_NAME)

def IsWindows():
    return PLATFORM == "windows"

def IsLinux():
    return PLATFORM == "linux"

def IsMacos():
    return PLATFORM == "darwin"