CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# vars
SET(META_PROJECT_NAME       "bluePrintCmake")
SET(META_EXTRUTABLE_NAME    ${META_PROJECT_NAME})

SET(SRC_DIR                 src/)

# set stuff
PROJECT(bluePrint_cmake)
FILE(GLOB SRC_FILES
        ${SRC_DIR}*.cpp
        ${SRC_DIR}*.h)


# extrutable
add_executable(
        ${META_PROJECT_NAME}
        ${SRC_FILES})