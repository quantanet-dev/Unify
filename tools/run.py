import globals, os, subprocess

if (globals.IsWindows()):
    subprocess.call(["{}/{}.{}".format(globals.EXECUTABLE_PATH, globals.PROJECT_NAME, "exe")], cwd=globals.EXECUTABLE_PATH)

if (globals.IsLinux()):
    subprocess.call(["{}/{}".format(globals.EXECUTABLE_PATH, globals.PROJECT_NAME)], cwd=globals.EXECUTABLE_PATH)

if (globals.IsMacos()):
    subprocess.call(["{}/{}".format(globals.EXECUTABLE_PATH, globals.PROJECT_NAME)], cwd=globals.EXECUTABLE_PATH)