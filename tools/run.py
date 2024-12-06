import globals, sys, subprocess

ret = 0

if (globals.IsWindows()):
    ret = subprocess.call(["{}/{}.{}".format(globals.EXECUTABLE_PATH, globals.PROJECT_NAME, "exe")], cwd=globals.EXECUTABLE_PATH)

if (globals.IsLinux()):
    ret = subprocess.call(["{}/{}".format(globals.EXECUTABLE_PATH, globals.PROJECT_NAME)], cwd=globals.EXECUTABLE_PATH)

if (globals.IsMacos()):
    ret = subprocess.call(["{}/{}".format(globals.EXECUTABLE_PATH, globals.PROJECT_NAME)], cwd=globals.EXECUTABLE_PATH)

sys.exit(ret)