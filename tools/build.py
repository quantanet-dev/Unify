import globals, os, subprocess, sys

ret = 0

if globals.IsWindows():
    VS_BUILD_PATH = os.environ["VS_BUILD_PATH"][8:-1]
    VS_BUILD_PATH = "C:\\\\" + VS_BUILD_PATH.replace("/", "\\\\")
    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(globals.CONFIG)])

if globals.IsLinux():
    ret = subprocess.call(["make", "-C", "config={}".format(globals.CONFIG)])

if globals.IsMacos():
    ret = subprocess.call(["xcodebuild", "-project", "./{}/{}.xcodeproj".format(globals.PROJECT_NAME, globals.PROJECT_NAME), "-configuration", "{}".format(globals.CONFIG)])

sys.exit(ret)