cmake_minimum_required(VERSION 3.3.2)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
string (APPEND CMAKE_CXX_FLAGS " -std=c++1z")
string (APPEND CMAKE_CXX_FLAGS " -fPIC")
string (APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer")
#string (APPEND CMAKE_CXX_FLAGS " -flto=thin")
string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
string (APPEND CMAKE_CXX_FLAGS_RELEASE " -Ofast -mtune=native -march=native")

set(ENABLE_TESTS OFF CACHE BOOL "Enable tests")
set(ENABLE_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")

include_directories("${CMAKE_SOURCE_DIR}/include")

include(${CMAKE_SOURCE_DIR}/cmake/antlr.cmake)

find_package(Cython REQUIRED)

### END SETUP ###

add_subdirectory(auxiliary)

set(LIB_SRC_FILES "")
add_subdirectory(lib)

if (ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (ENABLE_BENCHMARKS)
  include( "${CMAKE_SOURCE_DIR}/cmake/ExternalGoogleBenchmarks.cmake" )
  add_subdirectory(benchmarks)
endif()

### END SOURCE FILES ###

add_library(corelib STATIC $<TARGET_OBJECTS:aux_parsing> ${LIB_SRC_FILES})
target_link_libraries(corelib libantlr4-runtime.a)
add_dependencies(corelib antlr4cpp)

include(${CMAKE_SOURCE_DIR}/cmake/compile_module.cmake)

# END COMPILING

add_custom_target(tidy COMMAND python2 /usr/share/clang/run-clang-tidy.py "-header-filter=-benchmark.h" "-checks=bugprone-*,clang-analyzer-*,misc-*,modernize-*,performance-*,readability-*" > tidy.txt DEPENDS corelib)
# END SPECIAL TARGETS
