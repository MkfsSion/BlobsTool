cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(HASH_SRCS ../src/BlobHash.cpp hashtest.cpp)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
add_executable(hashtest ${HASH_SRCS})
add_compile_definitions(HASHTEST_NAME="hashtest")
IF(CMAKE_SYSTEM_NAME MATCHES "Linux" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_link_libraries(hashtest crypto stdc++fs)
ELSE()
    target_link_libraries(hashtest crypto)
ENDIF()