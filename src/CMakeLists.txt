cmake_minimum_required(VERSION 3.4)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
aux_source_directory(. BLOBSTOOL_SRCS)
add_executable(blobstool ${BLOBSTOOL_SRCS})
target_link_libraries(blobstool crypto)
