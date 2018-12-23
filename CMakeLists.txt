cmake_minimum_required(VERSION 3.4)
project(BlobsTool)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")
add_subdirectory(src)
add_subdirectory(tests)