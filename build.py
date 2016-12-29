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



# ANDROID
def crossAndroid(api):
    cleanCmake()
    print("[ANDROID] API '%s'" % api)
    okABIs = ''

    for abi in ANDROID_ABIS:
        print("[ANDROID] build abi '%s'" % abi)
        call(['cmake',
              '-DCMAKE_TOOLCHAIN_FILE=' + ANDROID_TOOLCHAIN,
              '-DANDROID_NATIVE_API_LEVEL=' + api,
              '-DANDROID_ABI=' + abi,
              '..'])
        ok = not call(['make'])
        if ok:
            okABIs += abi + ", "

    okApk = False
    if (okABIs != ''):
        print("[ANDROID] create apk")
        okApk = not call(['make', 'BuildApk'])

    print("\n[ANDROID] -- summary ----------------------------------")
    print("[ANDROID] SUCCESSFULLY build for '%s' " % okABIs)
    print("[ANDROID] build APK %s " % ('SUCCESSFULLY' if okApk else 'ERROR'))


# WINDOWS
def crossWindows():
    print("[WINDOWS] windows cross build is not supported (will come later)")


# NATIVE
def native():
    cleanCmake()
    print("[NATIVE] build")

    call(['cmake',
          '..'])
    okMake = not call(['make'])

    okPack = False
    if okMake:
        print("[NATIVE] create package")
        okPack = not call(['make', 'package'])

    print("\n[NATIVE] -- summary ----------------------------------")
    print("[NATIVE] build  '%s' " %         ('SUCCESSFULLY' if okMake else 'ERROR'))
    print("[NATIVE] create package %s " %   ('SUCCESSFULLY' if okPack else 'ERROR'))


def cleanCmake():
    print("\n[CLEAN] clean all cmake files in '%s'" % os.getcwd())

    for file in listFiles(['*.cmake', '*.txt', 'Makefile', 'CMakeFiles', '_CPack*', 'source']):
        if os.path.isfile(file):
            os.remove(file)
        elif os.path.isdir(file):
            shutil.rmtree(file)
        #print("remove " + file)



# ## helper
def listFiles(listWildcard):
    files = []
    for w in listWildcard:
        files.extend(glob.glob(w))
    return files



if __name__ == "__main__":
    main(sys.argv[1:])
