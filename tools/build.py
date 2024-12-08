import globals, os, subprocess, sys

ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe", "/c", globals.MSBUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(globals.PLATFORM_BUILD_CONFIG)], cwd=globals.BASE_PATH)

if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(globals.PLATFORM_BUILD_CONFIG.lower())], cwd=globals.BASE_PATH)

if globals.IsMacos():
    ret = subprocess.call(["make", "config={}".format(globals.PLATFORM_BUILD_CONFIG)], cwd=globals.BASE_PATH)

sys.exit(ret) 