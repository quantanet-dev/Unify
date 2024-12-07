import globals, os, subprocess, sys

ret = 0

if globals.IsWindows():
    VS_BUILD_PATH = os.environ["VS_BUILD_PATH"][8:-1]
    VS_BUILD_PATH = "C:\\\\" + VS_BUILD_PATH.replace("/", "\\\\")
    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(globals.CONFIG)])

if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(globals.CONFIG.lower())])

if globals.IsMacos():
    ret = subprocess.call(["make", "config={}".format(globals.CONFIG.lower())])
    #ret = subprocess.call(["sudo", "-s", "cp", "-R", "{}/libunify2.dylib".format(os.curdir), "//usr/local/lib/"], cwd=globals.LIB_PATH)
sys.exit(ret)