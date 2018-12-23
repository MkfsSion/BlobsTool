cmake_minimum_required(VERSION 3.4)

set(HASH_SRCS ../src/BlobHash.cpp hashtest.cpp)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
add_executable(hashtest ${HASH_SRCS})
target_link_libraries(hashtest crypto ssl)