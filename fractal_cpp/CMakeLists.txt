cmake_minimum_required(VERSION 3.3.2)


# Set compiler flags
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
string (APPEND CMAKE_CXX_FLAGS " -std=c++1z")
string (APPEND CMAKE_CXX_FLAGS " -fPIC")
string (APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer")
#string (APPEND CMAKE_CXX_FLAGS " -flto=thin")
string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
string (APPEND CMAKE_CXX_FLAGS_RELEASE " -Ofast -mtune=native -march=native")

# Set cache options
set(ENABLE_TESTS OFF CACHE BOOL "Enable tests")
set(ENABLE_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")

# Append system wide include directories
include_directories("${CMAKE_SOURCE_DIR}/include")

# Generate antlr files
include( "${CMAKE_SOURCE_DIR}/cmake/ExternalAntlr4Cpp.cmake" )
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories( ${ANTLR4CPP_LIBS} )
antlr4cpp_process_grammar(fractal_parse antlr
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemLexer.g4
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemParser.g4)
include_directories(${antlr4cpp_include_dirs_antlr})

find_package(Cython REQUIRED)

### END SETUP ###

add_subdirectory(auxiliary)

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

# Compile main output
add_library(fractalgen SHARED $<TARGET_OBJECTS:aux_python_bridge>)

target_link_libraries(fractalgen python3.6m lib_core)

target_compile_options(fractalgen PUBLIC -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g
  -fwrapv -O3 -Wall -march=x86-64 -mtune=generic -O2 -pipe
  -fstack-protector-strong -fno-plt)

set_target_properties(fractalgen PROPERTIES PREFIX "")
set_target_properties(fractalgen PROPERTIES OUTPUT_NAME "fractalgen")

# END COMPILING

# Add clang-tidy target
add_custom_target(tidy COMMAND python2 /usr/share/clang/run-clang-tidy.py "-header-filter=-benchmark.h" "-checks=bugprone-*,clang-analyzer-*,misc-*,modernize-*,performance-*,readability-*" > tidy.txt DEPENDS corelib)

# Add doxygen target
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
# END SPECIAL TARGETS
