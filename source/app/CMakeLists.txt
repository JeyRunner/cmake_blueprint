# Target
set(TARGET ${PROJECT_NAME})
set(SRC)


# files
#file(GLOB SRC_FILES
#        ${SOURCE_DIR}*.cpp
#        ${SOURCE_DIR}*.c
#        ${INCLUDE_DIR}*.h)
set(SRC_FILES source/main.cpp source/SDL_android_main.c)

set(ANDROID_PACKAGE_NAME "com.blueprint.cmake")

#
# extrutable / Lib
#
if (ANDROID)
    #set(SRC_FILES ${SRC_FILES} ${DEPENDENCIES_SDL2_DIR}/src/main/android/SDL_android_main.c)
    add_library(
            ${TARGET}
            SHARED
            ${SRC_FILES})
    #set_target_properties(
    #        ${TARGET} PROPERTIES
    #        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB}/${ANDROID_NDK_ABI_NAME})

    string(REGEX REPLACE "\\." "_" ANDROID_PACKAGE_ ${ANDROID_PACKAGE_NAME})
    add_definitions( -DANDROID_FUNC_PREFIX=Java_${})
else ()
    add_executable(
            ${TARGET}
            ${SRC_FILES})
endif ()


#
# Project options
#
set_target_properties(${TARGET}
        PROPERTIES
        ${DEFAULT_PROJECT_OPTIONS}
        FOLDER "appfolder/"
        )


#
# Include directories
#
target_include_directories(${TARGET}
        PRIVATE
        ${PROJECT_BINARY_DIR}/source/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include

        PUBLIC
        ${DEFAULT_INCLUDE_DIRECTORIES}
        )


#
# Libraries
#
target_link_libraries(${TARGET}
       # PRIVATE

        #PUBLIC
        #pthread rt freetype GLEW GL SDL2
        ${DEFAULT_LIBRARIES}
        )
message(STATUS LinkLibs: "${DEFAULT_LIBRARIES}")
message(STATUS LinkLibDir: "${DEPENDENCIES_FREETYPE_DIR}")

# ########################################
#
# Deployment
#

# Self
install(TARGETS ${TARGET}
        RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
        LIBRARY DESTINATION ${INSTALL_LIB} COMPONENT runtime
        ARCHIVE DESTINATION ${INSTALL_ARCH} COMPONENT develope
        )

# Header files
install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${INSTALL_INCLUDE}
        COMPONENT develope
        )


# android build apk
if (ANDROID)
    android_create_apk(
            ${TARGET}                       # name
            "com.blueprint.cmake"           # package name
            ${OUTPUT}/${WRAPPER_ANDROID}    # build dir for all android files
            ${OUTPUT}/lib                   # libs to use from java
            ${WRAPPER_ANDROID_DIR}          # dir of AndroidManifest..
            ""                              # asserts dir
    )
endif ()
