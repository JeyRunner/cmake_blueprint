
# Set output directories
function(setOutDir ALL BIN LIB ARCH PACK)
    set(OUTPUT                          ${CMAKE_SOURCE_DIR}/${ALL}     PARENT_SCOPE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/${BIN}     PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/${LIB}     PARENT_SCOPE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/${ARCH}    PARENT_SCOPE)

    set(OUTPUT_BIN                      ${CMAKE_SOURCE_DIR}/${BIN}     PARENT_SCOPE)
    set(OUTPUT_LIB                      ${CMAKE_SOURCE_DIR}/${LIB}     PARENT_SCOPE)
    set(OUTPUT_ARCHIVE                  ${CMAKE_SOURCE_DIR}/${ARCH}    PARENT_SCOPE)
    set(OUTPUT_PACKAGE                  ${CMAKE_SOURCE_DIR}/${PACK}    PARENT_SCOPE)
endfunction(setOutDir)


# Meta information about the project
function(setMetaProject
        NAME DISCRIPITOIN
        VERSION_MAJOR VERSION_MINOR VERSION_PATCH
        AUTHOR)
    set(META_PROJECT_NAME        ${NAME}                                PARENT_SCOPE)
    set(META_PROJECT_DESCRIPTION ${DISCRIPITOIN}                        PARENT_SCOPE)
    set(META_PROJECT_AUTHOR      ${AUTHOR}                              PARENT_SCOPE)
    set(META_VERSION_MAJOR       ${VERSION_MAJOR}                       PARENT_SCOPE)
    set(META_VERSION_MINOR       ${VERSION_MINOR}                       PARENT_SCOPE)
    set(META_VERSION_PATCH       ${VERSION_PATCH}                       PARENT_SCOPE)
    set(VERSION                  "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(META_VERSION             ${VERSION}                             PARENT_SCOPE)
    set(META_NAME_VERSION        "${NAME}-${VERSION}"                   PARENT_SCOPE)
endfunction()



# cpack
function(setupCPack)
    if(UNIX)
        SET(CPACK_GENERATOR "DEB"                                       PARENT_SCOPE)
        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER ${META_PROJECT_AUTHOR}      PARENT_SCOPE)
    endif()

    set(CPACK_COMPONENTS_ALL                ${INSTALL_COMPONENTS}       PARENT_SCOPE)
    set(CPACK_PACKAGE_NAME                  ${META_PROJECT_NAME}        PARENT_SCOPE)
    set(CPACK_PACKAGE_VENDOR                ""                          PARENT_SCOPE)
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   ${META_PROJECT_DESCRIPTION} PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION               ${META_VERSION}             PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION_MAJOR         ${META_VERSION_MAJOR}       PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION_MINOR         ${META_VERSION_MINOR}       PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION_PATCH         ${META_VERSION_PATCH}       PARENT_SCOPE)
    set(CPACK_PACKAGE_INSTALL_DIRECTORY     ${META_PROJECT_NAME}        PARENT_SCOPE)

    include(CPack)
endfunction(setupCPack)