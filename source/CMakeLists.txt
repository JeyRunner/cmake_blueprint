# version header
configure_file(meta/version.h.in ${OUTPUT_INCLUDE}/version.h)

# sub folders
add_subdirectory(app)