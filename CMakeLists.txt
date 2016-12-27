CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
INCLUDE(cmake/buildHelper.cmake)

# vars
SET(META_PROJECT_NAME       "bluePrintCmake")
SET(META_EXTRUTABLE_NAME    ${META_PROJECT_NAME})

SET(SRC_DIR                 src/)
SET(OUT_DIR                 bin/)
SET(TARGET                  ${META_PROJECT_NAME})

# set stuff
PROJECT(bluePrint_cmake)
FILE(GLOB SRC_FILES
        ${SRC_DIR}*.cpp
        ${SRC_DIR}*.h)

# set output directories
setOutDir(bin)


# extrutable
add_executable(
        ${TARGET}
        ${SRC_FILES})