# compile dependencies
# and download first
execute_process(COMMAND git submodule update --init --recursive)


# -- SDL2 -------------------------------------------------
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)
set(SDL_STATIC  ON CACHE BOOL    "Build the static SDL library")
set(SDL_SHARED  OFF  CACHE BOOL  "Build the shared SDL library")
set(PTHREADS    OFF  CACHE BOOL  "Pthread support")
add_subdirectory(SDL2)

set(DEPENDENCIES_SDL2_INCLUDE   ${CMAKE_SOURCE_DIR}/dependencies/SDL2/include   PARENT_SCOPE)
set(DEPENDENCIES_SDL2_LIB       SDL2                                            PARENT_SCOPE)
