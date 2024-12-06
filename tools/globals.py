import os
import sys
import platform

ENGINE_NAME = "unify2"
PROJECT_NAME = "unifyeditor2"
VERSION_MAJOR = 1
VERSION_MINOR = 0
CONFIG = "Debug"

TOOLS_DIR = "tools"
EXECUTABLE_PATH = "{}/bin/{}/{}".format(os.getcwd(), CONFIG, PROJECT_NAME, PROJECT_NAME)

PLATFORM = sys.platform

for x in platform.uname():
    if "microsoft" in x.lower():
        PLATFORM = "windows"
        break

def IsWindows():
    return PLATFORM == "windows"

def IsLinux():
    return PLATFORM == "linux"

def IsMacos():
    return PLATFORM == "darwin"