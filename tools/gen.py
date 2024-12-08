import globals, subprocess, sys

ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe", "/c", "premake\\premake5", "gmake2"])
    if ret == 0:
        ret = subprocess.call(["cmd.exe", "/c", "premake\\premake5", "vs2022"])

if globals.IsLinux():
    ret = subprocess.call(["chmod", "+x", "premake/premake5.linux"])
    if ret == 0:
        ret = subprocess.call(["premake/premake5.linux", "gmake2"])

if globals.IsMacos():
    ret = subprocess.call(["chmod", "+x", "premake/premake5"])
    if ret == 0:
        ret = subprocess.call(["premake/premake5", "gmake2"])

sys.exit(ret)