import globals, sys, os

print("Unify Build Tools v{}.{}".format(globals.TOOLSET_VERSION_MAJOR, globals.TOOLSET_VERSION_MINOR))
print("Platform: {}-{}".format(globals.PLATFORM, globals.ARCHITECTURE))

sys.exit(0)