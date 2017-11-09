cmake_minimum_required(VERSION 3.3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -mtune=native -march=native")

set(ENABLE_TESTS OFF CACHE BOOL "Enable tests")
set(ENABLE_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")

include_directories("${CMAKE_SOURCE_DIR}/include")

include(${CMAKE_SOURCE_DIR}/cmake/antlr.cmake)

enable_testing()

### END SETUP ###

add_subdirectory(auxiliary)

set(LIB_SRC_FILES "")
add_subdirectory(lib)

if (ENABLE_TESTS)
  add_subdirectory(tests)
endif()

if (ENABLE_BENCHMARKS)
  include( "${CMAKE_SOURCE_DIR}/cmake/ExternalGoogleBenchmarks.cmake" )
  add_subdirectory(benchmarks)
endif()

### END SOURCE FILES ###

include(${CMAKE_SOURCE_DIR}/cmake/compile_module.cmake)

