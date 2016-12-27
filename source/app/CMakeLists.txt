# Target
set(TARGET ${META_NAME_VERSION}-Linux)
set(SRC)


# files
file(GLOB SRC_FILES
        ${SOURCE_DIR}*.cpp
        ${INCLUDE_DIR}*.h)



#
# extrutable / Lib
#
add_executable(
        ${TARGET}
        ${SRC_FILES})


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
        PRIVATE

        PUBLIC
        ${DEFAULT_LIBRARIES}
        )



# ########################################
#
# Deployment
#

# Self
install(TARGETS ${TARGET}
        RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
        LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
        ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT develope
        )

# Header files
install(DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${INSTALL_INCLUDE}
        COMPONENT develope
        )
