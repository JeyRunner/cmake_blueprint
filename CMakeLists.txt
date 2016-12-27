cmake_minimum_required(VERSION 3.0)

# Include cmake modules
include(cmake/buildHelper.cmake)



# ------------------------------------
# -- Project infos

# Meta information about the project
set(META_PROJECT_NAME        "bluePrintCmake")
set(META_PROJECT_DESCRIPTION "blue print cmake for c++")
set(META_PROJECT_AUTHOR      "Joshua Johannson")
set(META_VERSION_MAJOR       "1")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "0")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION} (${META_VERSION_REVISION})")

# install
set(INSTALL_BIN         bin)
set(INSTALL_LIB         lib)
set(INSTALL_INCLUDE     include)
set(INSTALL_COMPONENTS  applications libraries headers)

# ------------------------------------
# -- Project options
option(OPTION_CROSS_COMPILE_ANDROID     "Cross compile for android (need sdk and ndk)."                         ON)
option(OPTION_CROSS_COMPILE_WINDOWS     "Cross compile for windows (need sdk)."                                 OFF)
option(OPTION_CROSS_COMPILE_RASPBERRY   "Cross compile for rasperry pi (need compiler and raspi root folder)."  OFF)
option(OPTION_CROSS_COMPILE_OSX         "Cross compile for osx (need sdk)."                                     OFF)
option(OPTION_BUILD_TESTS               "Build tests."                                                          OFF)
option(OPTION_BUILD_EXAMPLES            "Build examples."                                                       OFF)



# set project name and output dir
project(${META_PROJECT_NAME})
setOutDir(
        build/bin
        build/lib
        build/installer)

# default dirs for targets
set(SOURCE_DIR  source/)
set(INCLUDE_DIR include/)


# source dir
add_subdirectory(source)


# ----------------------------------
# -- create installer
if(UNIX)
    SET(CPACK_GENERATOR "DEB")
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER ${META_PROJECT_AUTHOR})
endif()

SET(CPACK_OUTPUT_FILE_PREFIX build/install)
set(CPACK_COMPONENTS_ALL                ${INSTALL_COMPONENTS})
set(CPACK_PACKAGE_NAME                  ${META_PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR                "")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   ${META_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_VERSION               ${META_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR         ${META_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR         ${META_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH         ${META_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY     ${META_PROJECT_NAME})

include(CPack)