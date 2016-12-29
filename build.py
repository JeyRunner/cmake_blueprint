#!/usr/bin/python

# ############################
# build crossplatform via toolchain in cmake/

from optparse import OptionParser
import sys, getopt, os, glob, shutil
from subprocess import call

# VAR
ANDROID_ABIS = ['armeabi', 'armeabi-v7a'
                # 'armeabi-v7a with NEON', 'armeabi-v7a with VFPV3',
                # 'armeabi-v6 with VFP',
                # 'x86',
                # 'arm64-v8a', 'x86_64', 'mips64']
                ]
ANDROID_TOOLCHAIN = 'cmake/android.toolchain.cmake'
error = False


def main(argv):
    parser = OptionParser()
    parser.add_option("-a", "--android", dest="android",
                      help="cross compile for all ABI for android API('android-NUMBER')", metavar="API")
    parser.add_option("-w", "--windows", dest="windows", action="store_true",
                      help="cross compile for windows (coming soon)")
    parser.add_option("-n", "--native", dest="native", action="store_true",
                      help="build for host system")
    parser.add_option("-c", "--clean", dest="clean", action="store_true",
                      help="cleans only cmake files first, not compiled files")
    (options, args) = parser.parse_args()

    # go into build dir
    if not os.path.exists('build/'):
        os.makedirs('build/')
    os.chdir('build/')

    # check
    if (options.android is not None):
        crossAndroid(options.android)

    if (options.windows is not None):
        crossWindows()

    if (options.native is not None):
        native()

    if (options.clean is not None):
        cleanCmake()

    printCol("\n=============================================================", CYAN)
    if error:
        printCol("[__ALL__] ERROR", RED)
        exit(1)
    else:
        printCol("[__ALL__] SUCCESS", GREEN)


# ANDROID
def crossAndroid(api):
    cleanCmake()

    printCol("\n=============================================================\n"
             "[ANDROID] API '%s'" % api, CYAN)

    okABIs = ''

    for abi in ANDROID_ABIS:
        print("[ANDROID] build abi '%s'" % abi)
        run(['cmake',
             '-DCMAKE_TOOLCHAIN_FILE=' + ANDROID_TOOLCHAIN,
             '-DANDROID_NATIVE_API_LEVEL=' + api,
             '-DANDROID_ABI=' + abi,
             '..'])
        ok = not call(['make'])
        if ok:
            okABIs += abi + ", "

    okApk = False
    if (okABIs != ''):
        printCol("\n[ANDROID] create apk", CYAN)
        okApk = run(['make', 'BuildApk'])
    else:
        setError(True)

    setError(okApk)
    print("\n[ANDROID] -- summary ----------------------------------")
    printOk("[ANDROID] " + ("SUCCESSFULLY build for '" + okABIs + "'" if (okABIs != '') else 'ERROR'), okABIs != '')
    printOk("[ANDROID] build APK %s " % ('SUCCESSFULLY' if okApk else 'ERROR'), okApk)


# WINDOWS
def crossWindows():
    printCol("\n=============================================================\n"
             "[WINDOWS] windows cross build is not supported (will come later)", CYAN)


# NATIVE
def native():
    cleanCmake()

    printCol("\n=============================================================\n"
             "[NATIVE] build", CYAN)

    run(['cmake',
         '..'])
    okMake = run(['make'])
    setError(okMake)

    okPack = False
    if okMake:
        printCol("\n[NATIVE] create package", CYAN)
        okPack = run(['make', 'package'])
    setError(okPack)

    print("\n[NATIVE] -- summary ----------------------------------")
    printOk("[NATIVE] build  '%s' " % ('SUCCESSFULLY' if okMake else 'ERROR'), okMake)
    printOk("[NATIVE] create package %s " % ('SUCCESSFULLY' if okPack else 'ERROR'), okPack)


def cleanCmake():
    printCol("\n=============================================================\n"
             "[CLEAN] clean all cmake files in '" + os.getcwd() + "'", CYAN)

    for file in listFiles(['*.cmake', '*.txt', 'Makefile', 'CMakeFiles', '_CPack*', 'source']):
        if os.path.isfile(file):
            os.remove(file)
        elif os.path.isdir(file):
            shutil.rmtree(file)
            # print("remove " + file)


# ## helper
def run(command):
    s = ""
    for a in command:
        s += a + " "
    printCol(s, BLUE)
    return not call(command)


def listFiles(listWildcard):
    files = []
    for w in listWildcard:
        files.extend(glob.glob(w))
    return files


def setError(ok):
    global error
    error |= not ok


# print color
RED = "\033[1;31m"
BLUE = "\033[1;34m"
CYAN = "\033[1;36m"
GREEN = "\033[0;32m"
RESET = "\033[0;0m"
BOLD = "\033[;1m"
REVERSE = "\033[;7m"


def printCol(text, color):
    # sys.stdout.write(color)
    print(color + text + RESET)
    # sys.stdout.write(RESET)


def printOk(text, ok):
    if ok:
        printCol(text, GREEN)
    else:
        printCol(text, RED)


if __name__ == "__main__":
    main(sys.argv[1:])
