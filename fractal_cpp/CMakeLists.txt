cmake_minimum_required(VERSION 3.3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -mtune=native -march=native")

include_directories("${CMAKE_SOURCE_DIR}/include")

include(${CMAKE_SOURCE_DIR}/cmake/antlr.cmake)
include( "${CMAKE_SOURCE_DIR}/cmake/ExternalGoogleBenchmarks.cmake" )

enable_testing()

### END SETUP ###

add_subdirectory(auxiliary)

set(LIB_SRC_FILES "")
add_subdirectory(lib)

add_subdirectory(tests)

set(BENCH_SRC_FILES "")
add_subdirectory(benchmarks)

### END SOURCE FILES ###

include(${CMAKE_SOURCE_DIR}/cmake/compile_module.cmake)

