cmake_minimum_required(VERSION 3.0)

# Include cmake modules
include(cmake/buildHelper.cmake)
include(cmake/android.apk.cmake)


# ------------------------------------
# -- Project infos

# Meta information about the project
setMetaProject(
        "bluePrintCmake" "blue print cmake for c++"    # name, descrition
        1 1 1                                          # version
        "Joshua Johannson"                              # author
)

# set project name and output dir
project(${META_PROJECT_NAME})


# ------------------------------------
# -- Project options
#option(OPTION_CROSS_COMPILE_ANDROID     "Cross compile for android (need sdk and ndk)."                         ON)
#option(OPTION_CROSS_COMPILE_WINDOWS     "Cross compile for windows (need sdk)."                                 OFF)
#option(OPTION_CROSS_COMPILE_RASPBERRY   "Cross compile for rasperry pi (need compiler and raspi root folder)."  OFF)
#option(OPTION_CROSS_COMPILE_OSX         "Cross compile for osx (need sdk)."                                     OFF)
option(OPTION_BUILD_TESTS "Build tests." OFF)
option(OPTION_BUILD_EXAMPLES "Build examples." OFF)


# -----------------------------
# -- set BUILD out dirs
if (ANDROID)
    setOutDir(
            build       # general
            build/bin   # bin
            build/lib/${ANDROID_NDK_ABI_NAME}   # lib
            build/lib/${ANDROID_NDK_ABI_NAME}  # archiv
            build/pack  # package / installer / app
    )
else ()
    setOutDir(
            build       # general
            build/bin   # bin
            build/lib   # lib
            build/lib  # archiv
            build/pack  # package / installer / app
    )
endif ()


# -----------------------------
# -- set INSTALL out dirs
set(INSTALL_BIN bin)
set(INSTALL_LIB lib)
set(INSTALL_INCLUDE include)
set(INSTALL_COMPONENTS applications libraries headers)


# -----------------------------
# -- default SOURCE dirs for targets
set(SOURCE_DIR source/)
set(INCLUDE_DIR include/)


# ----------------------------------
# -- cross compile

# -- ANDROID -------------------------------------------------
# platform dependet wrappers
set(WRAPPER_ANDROID platform/android)
set(WRAPPER_ANDROID_DIR ${CMAKE_SOURCE_DIR}/${WRAPPER_ANDROID})

set(ANDROID_APK_API_LEVEL "25" CACHE STRING "Android APK API level")
set(ANDROID_APK_INSTALL "1" CACHE BOOL "Install created apk file on the device automatically?")
set(ANDROID_APK_RUN "1" CACHE BOOL "Run created apk file on the device automatically?")
set(ANDROID_APK_SIGNER_KEYSTORE "~/my-release-key.keystore" CACHE STRING "Keystore for signing the apk file")
set(ANDROID_APK_SIGNER_ALIAS "myalias" CACHE STRING "Alias for signing the apk file")

if (ANDROID)
    add_definitions(-DGL_GLEXT_PROTOTYPES)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_C_STANDARD_LIBRARIES "-landroid -llog -lGLESv1_CM -lGLESv2")
    set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES}")
endif ()


link_directories(${OUTPUT_LIB})

# ------------------------------------
# -- Dependences
add_subdirectory(dependencies)


# default headers, libs
set(DEFAULT_INCLUDE_DIRECTORIES
        ${DEPENDENCIES_SDL2_INCLUDE})

set(DEFAULT_LIBRARIES
        ${DEPENDENCIES_SDL2_LIB})


# source dir
add_subdirectory(source)


# ----------------------------------
# -- create installer
if (UNIX)
    SET(CPACK_GENERATOR "DEB")
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER ${META_PROJECT_AUTHOR})
endif ()

SET(CPACK_OUTPUT_FILE_PREFIX ${OUTPUT_PACKAGE})
set(CPACK_COMPONENTS_ALL ${INSTALL_COMPONENTS})
set(CPACK_PACKAGE_NAME ${META_PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${META_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION ${META_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR ${META_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${META_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${META_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${META_PROJECT_NAME})

include(CPack)
