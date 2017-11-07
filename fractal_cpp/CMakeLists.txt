cmake_minimum_required(VERSION 3.3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++1z")

include_directories("${CMAKE_SOURCE_DIR}/include")

include(${CMAKE_SOURCE_DIR}/cmake/antlr.cmake)

### END SETUP ###

add_subdirectory(auxiliary)

set(LIB_SRC_FILES "")
add_subdirectory(lib)

set(TEST_SRC_FILES "")
add_subdirectory(tests)

### END SOURCE FILES ###

enable_testing()
add_executable(testing ${TEST_SRC_FILES})
add_test(NAME main_test COMMAND testing)

include(${CMAKE_SOURCE_DIR}/cmake/compile_module.cmake)
