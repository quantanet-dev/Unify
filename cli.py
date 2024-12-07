import os, sys, subprocess

from tools import globals

def menu():
    print("=======================")
    print("Unify2 Build Tools v{}.{}".format(globals.VERSION_MAJOR, globals.VERSION_MINOR))
    print("=======================\n")
    print("[1] Generate Project")
    print("[2] Build Executable")
    print("[3] Run Executable")
    print("[4] Exit")

def RunCommand(cmd):
    ret = 0
    script = "{}/{}/{}.py".format(os.getcwd(), globals.TOOLS_DIR, cmd)
    if os.path.exists(script):
        print("Executing: {}".format(cmd).upper())
        print("=======================\n")
        ret = subprocess.call(["python3", script])
    else:
        print("Invalid command or filepath: ", cmd)
        ret = -1
    return ret

if (len(sys.argv) < 2):
    menu()
    print()
    option = int(input("Select an option: "))

    while option != 0:
        if option == 1:
            print()
            RunCommand("gen")
            pass
        elif option == 2:
            print()
            RunCommand("build")
            pass
        elif option == 3:
            print()
            RunCommand("run")
            pass
        elif option == 4:
            print()
            sys.exit(0)
            pass
        else:
            print("Invalid Option")
        
        print()
        menu()
        print()
        option = int(input("Select an option: "))
else:
    for i in range(1, len (sys.argv)):
        cmd = sys.argv[i]
        print("\n=======================")
        print("Unify2 Build Tools v{}.{}".format(globals.VERSION_MAJOR, globals.VERSION_MINOR))
        print("=======================\n")
        if RunCommand(cmd) != 0:
            break