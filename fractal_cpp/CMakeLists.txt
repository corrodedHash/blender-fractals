cmake_minimum_required(VERSION 3.3.2)


# Set compiler flags
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(MSVC)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
  # Need to make Visual C++ conform standard
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ze")
  # Default debug flags are OK
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()

  if (FRAC_ENABLE_FUZZER)
    string( APPEND CMAKE_CXX_FLAGS " -fsanitize-coverage=trace-pc-guard -fsanitize=address")
    string( APPEND CMAKE_CXX_FLAGS " -fprofile-instr-generate -fcoverage-mapping")
  endif()
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    string (APPEND CMAKE_CXX_FLAGS " -fcolor-diagnostics")
  else()
    message(STATUS "Not compiling with clang, disabling colored diagnostics")
  endif()
  string (APPEND CMAKE_CXX_FLAGS " -std=c++1z")
  string (APPEND CMAKE_CXX_FLAGS " -fPIC")
  string (APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer")
  #string (APPEND CMAKE_CXX_FLAGS " -flto=thin")
  string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address")
  string (APPEND CMAKE_CXX_FLAGS_RELEASE " -Ofast -mtune=native -march=native")

endif()

# Set cache options
set(FRAC_ENABLE_TESTS OFF CACHE BOOL "Enable tests")
set(FRAC_ENABLE_PYTHON ON CACHE BOOL "Build the python module")
set(FRAC_ENABLE_FUZZER OFF CACHE BOOL "Enable fuzzing")
set(FRAC_ENABLE_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")
set(FRAC_GENERATE_CYTHON ON CACHE BOOL "Generate the cython from the .pyx file, otherwise supply auxiliary/cython/fractalgen.cpp")

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

# Use cython
if (FRAC_GENERATE_CYTHON)
  find_package(Cython REQUIRED)
endif()

### END SETUP ###

add_subdirectory(auxiliary)

add_subdirectory(lib)

if (FRAC_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (FRAC_ENABLE_BENCHMARKS)
  include( "${CMAKE_SOURCE_DIR}/cmake/ExternalGoogleBenchmarks.cmake" )
  add_subdirectory(benchmarks)
endif()

if (FRAC_ENABLE_FUZZER)
  add_subdirectory(fuzzer)
endif()

### END SOURCE FILES ###

# Compile main output

if (FRAC_ENABLE_PYTHON)
  add_library(fractalgen SHARED $<TARGET_OBJECTS:aux_python_bridge>)

  target_link_libraries(fractalgen python3.7m lib_core)

  target_compile_options(fractalgen PUBLIC -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g
    -fwrapv -O3 -Wall -march=x86-64 -mtune=generic -O2 -pipe
    -fstack-protector-strong -fno-plt)

  set_target_properties(fractalgen PROPERTIES PREFIX "")
  set_target_properties(fractalgen PROPERTIES OUTPUT_NAME "fractalgen")
endif()

# END COMPILING

# Add clang-tidy target
add_custom_target(tidy COMMAND python2 /usr/share/clang/run-clang-tidy.py "-header-filter=-benchmark.h" "-checks=bugprone-*,clang-analyzer-*,misc-*,modernize-*,performance-*,readability-*" > tidy.txt DEPENDS lib_core)

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
