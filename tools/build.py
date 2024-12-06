import globals, os, subprocess

if globals.IsWindows():
    VS_BUILD_PATH = os.environ["VS_BUILD_PATH"][8:-1]
    VS_BUILD_PATH = "C:\\\\" + VS_BUILD_PATH.replace("/", "\\\\")
    subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}\\{}.sln".format("solution-files", globals.ENGINE_NAME), "/property:Configuration={}".format(globals.CONFIG)])

if globals.IsLinux():
    subprocess.call(["make", "-C", "{}".format("./solution-files/") , "config={}".format(globals.CONFIG)])

if globals.IsMacos():
    subprocess.call(["xcodebuild", "-project", "./{}/{}.xcodeproj".format("solution-files", globals.PROJECT_NAME), "-configuration", "{}".format(globals.CONFIG)])