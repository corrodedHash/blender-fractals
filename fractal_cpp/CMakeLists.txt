cmake_minimum_required(VERSION 3.3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

include_directories("${CMAKE_SOURCE_DIR}/include")

set(ANTLR4CPP_JAR_LOCATION ${CMAKE_BINARY_DIR}/antlr-complete.jar)
execute_process(COMMAND curl http://www.antlr.org/download/antlr-4.7-complete.jar --output ${ANTLR4CPP_JAR_LOCATION})
include( "${CMAKE_SOURCE_DIR}/cmake/ExternalAntlr4Cpp.cmake" )
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories( ${ANTLR4CPP_LIBS} )
antlr4cpp_process_grammar(fractal_parse antlr
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemLexer.g4
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemParser.g4)
include_directories(${antlr4cpp_include_dirs_antlr})

add_subdirectory(auxiliary)

set(LIB_SRC_FILES "")
add_subdirectory(lib)

add_library(fractalgen SHARED ${LIB_SRC_FILES} $<TARGET_OBJECTS:parsing> $<TARGET_OBJECTS:python_bridge>)

target_link_libraries(fractalgen python3.6m libantlr4-runtime.a)

add_dependencies(fractalgen antlr4cpp_generation_antlr)

target_compile_options(fractalgen PUBLIC -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g
  -fwrapv -O3 -Wall -march=x86-64 -mtune=generic -O2 -pipe
  -fstack-protector-strong -fno-plt)

set_target_properties(fractalgen PROPERTIES PREFIX "")
set_target_properties(fractalgen PROPERTIES OUTPUT_NAME "fractalgen")
