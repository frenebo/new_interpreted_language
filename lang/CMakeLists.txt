cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)

option(JS_ONLY "Compiles to native JS (No WASM)" OFF)

include_directories(src)


file(GLOB_RECURSE proj_SRC
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(lang ${proj_SRC})

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wswitch-enum")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

if(JS_ONLY)
	message(STATUS "Setting compilation target to native JavaScript")
	set(CMAKE_EXECUTABLE_SUFFIX ".js")
	set_target_properties(lang PROPERTIES LINK_FLAGS "-s WASM=0 -s EXPORTED_FUNCTIONS='[_main]'")
else(JS_ONLY)
	message(STATUS "Setting compilation target to WASM")
	set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
	set_target_properties(lang PROPERTIES LINK_FLAGS "-s WASM=1 -s BINARYEN_METHOD='native-wasm' -s EXPORTED_FUNCTIONS='[_main]'")
endif(JS_ONLY)
