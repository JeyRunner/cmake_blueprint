# compile dependencies


# -- SDL2 -------------------------------------------------
find_package(SDL2 QUIET)

if (SDL2_FOUND)
    message(STATUS "DEPENDENCY = SDL2 => Found includeDir: ${SDL2_INCLUDE_DIRS}, libDir:  ${SDL2_LIBDIR}")

    set(DEPENDENCIES_SDL2_INCLUDE ${SDL2_INCLUDE_DIRS} PARENT_SCOPE)
    set(DEPENDENCIES_SDL2_DIR ${SDL2_LIBDIR} PARENT_SCOPE)
    set(DEPENDENCIES_SDL2_LIB SDL2 PARENT_SCOPE)
else ()
    message(STATUS "DEPENDENCY = SDL2 => NOT found => will compile SDL")
    execute_process(COMMAND git submodule update --init --recursive dependencies/SDL2)

    if (ANDROID)
        set(SDL_STATIC ON CACHE BOOL "Build the static SDL library")
        set(SDL_SHARED OFF CACHE BOOL "Build the shared SDL library")
        set(DEPENDENCIES_SDL2_LIB SDL2 PARENT_SCOPE)
    else ()
        set(SDL_STATIC OFF CACHE BOOL "Build the static SDL library")
        set(SDL_SHARED ON CACHE BOOL "Build the shared SDL library")
        set(DEPENDENCIES_SDL2_LIB SDL2-2.0 PARENT_SCOPE)
    endif ()
    set(PTHREADS OFF CACHE BOOL "Pthread support")
    #set(DISKAUDIO  OFF)
    add_subdirectory(SDL2)

    set(DEPENDENCIES_SDL2_INCLUDE ${CMAKE_SOURCE_DIR}/dependencies/SDL2/include PARENT_SCOPE)
    set(DEPENDENCIES_SDL2_DIR ${CMAKE_SOURCE_DIR}/dependencies/SDL2 PARENT_SCOPE)
endif ()


# -- GLEW -------------------------------------------------
if (NOT ANDROID)
    find_package(GLEW QUIET)

    if (GLEW_FOUND)
        message(STATUS "DEPENDENCY = GLEW => Found includeDir: ${GLEW_INCLUDE_DIRS}, lib:  ${GLEW_LIBRARIES}")

        set(DEPENDENCIES_GLEW_INCLUDE ${GLEW_INCLUDE_DIRS} PARENT_SCOPE)
        set(DEPENDENCIES_GLEW_DIR ${GLEW_LIBDIR} PARENT_SCOPE)
        set(DEPENDENCIES_GLEW_LIB GLEW PARENT_SCOPE)
    else ()
        message(STATUS "DEPENDENCY = GLEW => NOT found => will compile GLEW")
        execute_process(COMMAND git submodule update --init --recursive dependencies/GLEW)

        #add_subdirectory(GLEW)

        #set(DEPENDENCIES_GLEW_INCLUDE   ${CMAKE_SOURCE_DIR}/dependencies/GLEW/include   PARENT_SCOPE)
        #set(DEPENDENCIES_GLEW_DIR       ${CMAKE_SOURCE_DIR}/dependencies/GLEW           PARENT_SCOPE)
        #set(DEPENDENCIES_GLEW_LIB       glew                                            PARENT_SCOPE)
    endif ()
endif ()


# -- GL -------------------------------------------------
if (NOT ANDROID)
    find_package(OpenGL REQUIRED)

    if (OpenGL_FOUND)
        message(STATUS "DEPENDENCY = OpenGL => Found includeDir: ${OPENGL_INCLUDE_DIR}, lib:  ${OPENGL_gl_LIBRARY}")

        set(DEPENDENCIES_OpenGL_INCLUDE ${OPENGL_INCLUDE_DIR} PARENT_SCOPE)
        set(DEPENDENCIES_OpenGL_DIR ${OPENGL_gl_LIBRARY} PARENT_SCOPE)
        set(DEPENDENCIES_OpenGL_LIB GL PARENT_SCOPE)
    endif ()
else ()
    set(DEPENDENCIES_OpenGL_INCLUDE PARENT_SCOPE)
    set(DEPENDENCIES_OpenGL_DIR $ PARENT_SCOPE)
    set(DEPENDENCIES_OpenGL_LIB GLESv2 PARENT_SCOPE)
endif ()


# -- GLM -------------------------------------------------
set(DEPENDENCIES_GLM_INCLUDE ${CMAKE_SOURCE_DIR}/dependencies/glm/glm PARENT_SCOPE)