import globals, subprocess

if globals.IsWindows():
    subprocess.call(["cmd.exe", "/c", "premake\\premake5", "vs2022"])

if globals.IsLinux():
    subprocess.call(["premake/premake5.linux", "gmake2"])

if globals.IsMacos():
    subprocess.call(["premake/premake5", "gmake2"])
    subprocess.call(["premake/premake5", "xcode4"])