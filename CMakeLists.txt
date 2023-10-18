cmake_minimum_required(VERSION 3.9)
project(labs03)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "Debug")

include_directories("include")
add_library(lib "src/lib.c")
add_executable(main "src/main.c")

target_link_libraries(main lib)
