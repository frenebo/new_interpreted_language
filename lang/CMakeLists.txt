cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)

include_directories(src)


file(GLOB_RECURSE proj_SRC
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(lang ${proj_SRC})

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wswitch-enum")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
