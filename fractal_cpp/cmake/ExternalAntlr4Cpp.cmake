# -*- mode:cmake -*-

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.2)
PROJECT(antlr4cpp_fetcher CXX)
INCLUDE(ExternalProject)
FIND_PACKAGE(Git REQUIRED)

# only JRE required
FIND_PACKAGE(Java COMPONENTS Runtime REQUIRED)

############ Download and Generate runtime #################
set(ANTLR4CPP_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/antlr4cpp)

# external repository
# GIT_REPOSITORY     https://github.com/antlr/antlr4.git
set(ANTLR4CPP_EXTERNAL_REPO "https://github.com/antlr/antlr4.git")
set(ANTLR4CPP_EXTERNAL_TAG  "4.7")
set(ANTLR4CPP_TOOL_URL "http://www.antlr.org/download/antlr-4.7-complete.jar")
set(ANTLR4CPP_TOOL_NAME "antlr-complete.jar")
set(ANTLR4CPP_TOOL_LOCATION "${ANTLR4CPP_EXTERNAL_ROOT}/${ANTLR4CPP_TOOL_NAME}")

# default path for source files
if (NOT ANTLR4CPP_GENERATED_SRC_DIR)
  set(ANTLR4CPP_GENERATED_SRC_DIR ${CMAKE_BINARY_DIR}/antlr4cpp_generated_src)
endif()

# Fetching the tool
add_custom_command(OUTPUT ${ANTLR4CPP_TOOL_LOCATION} COMMAND curl --silent --output ${ANTLR4CPP_TOOL_LOCATION} ${ANTLR4CPP_TOOL_URL})
add_custom_target(antlrtool DEPENDS ${ANTLR4CPP_TOOL_LOCATION})

ExternalProject_ADD(
  #--External-project-name------
  antlr4cpp
  #--Depend-on-antrl-tool-----------
  DEPENDS antlrtool
  #--Core-directories-----------
  PREFIX             ${ANTLR4CPP_EXTERNAL_ROOT}
  #--Download step--------------
  GIT_REPOSITORY     ${ANTLR4CPP_EXTERNAL_REPO}
  GIT_SHALLOW 1
  # GIT_TAG          ${ANTLR4CPP_EXTERNAL_TAG}
  TIMEOUT            10
  LOG_DOWNLOAD       ON
  #--Update step----------
  #UPDATE_COMMAND     ${GIT_EXECUTABLE} pull
  UPDATE_COMMAND ""
  #--Patch step----------
  # PATCH_COMMAND sh -c "cp <SOURCE_DIR>/scripts/CMakeLists.txt <SOURCE_DIR>"
  #--Configure step-------------
  SOURCE_SUBDIR runtime/Cpp
  CMAKE_ARGS -DCMAKE_CXX_FLAGS=-fPIC -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE} -DANTLR4CPP_JAR_LOCATION=${ANTLR4CPP_TOOL_LOCATION} -DBUILD_SHARED_LIBS=ON -BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  LOG_CONFIGURE ON
  #--Build step-----------------
  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
  LOG_BUILD ON
  #--Install step---------------
  # INSTALL_COMMAND    ""
  # INSTALL_DIR ${CMAKE_BINARY_DIR}/
  #--Install step---------------
  # INSTALL_COMMAND    ""
)

ExternalProject_Get_Property(antlr4cpp INSTALL_DIR)

list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime)
foreach(src_path misc atn dfa tree support)
  list(APPEND ANTLR4CPP_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime/${src_path})
endforeach(src_path)

set(ANTLR4CPP_LIBS "${INSTALL_DIR}/lib")

# antlr4_shared ${INSTALL_DIR}/lib/libantlr4-runtime.so
# antlr4_static ${INSTALL_DIR}/lib/libantlr4-runtime.a

############ Generate runtime #################
# macro to add dependencies to target
#
# Param 1 project name
# Param 1 namespace (postfix for dependencies)
# Param 2 Lexer file (full path)
# Param 3 Parser File (full path)
#
# output
#
# antlr4cpp_src_files_{namespace} - src files for add_executable
# antlr4cpp_include_dirs_{namespace} - include dir for generated headers
# antlr4cpp_generation_{namespace} - for add_dependencies tracking

macro(antlr4cpp_process_grammar
    antlr4cpp_project
    antlr4cpp_project_namespace
    antlr4cpp_grammar_lexer
    antlr4cpp_grammar_parser)

  get_filename_component(antlr4cpp_grammar_lexer_name "${antlr4cpp_grammar_lexer}" NAME_WE)
  get_filename_component(antlr4cpp_grammar_parser_name "${antlr4cpp_grammar_parser}" NAME_WE)
  # Find all the input files
  list(APPEND generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_grammar_lexer_name}.cpp)
  list(APPEND generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_grammar_parser_name}.cpp)
  list(APPEND generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_grammar_parser_name}Listener.cpp)
  list(APPEND generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_grammar_parser_name}Visitor.cpp)
  list(APPEND generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_grammar_parser_name}BaseListener.cpp)
  list(APPEND generated_files ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}/${antlr4cpp_grammar_parser_name}BaseVisitor.cpp)
  add_custom_command(OUTPUT ${generated_files}
    COMMAND
    ${CMAKE_COMMAND} -E make_directory ${ANTLR4CPP_GENERATED_SRC_DIR}
    COMMAND
    "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR4CPP_TOOL_LOCATION}" -Werror -Dlanguage=Cpp -listener -visitor -o "${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}" -package ${antlr4cpp_project_namespace} "${antlr4cpp_grammar_lexer}" "${antlr4cpp_grammar_parser}"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS "${antlr4cpp_grammar_lexer}" "${antlr4cpp_grammar_parser}")
  add_custom_target("antlr4cpp_generation_${antlr4cpp_project_namespace}"
    DEPENDS antlrtool "${generated_files}"
    )
    # export generated cpp files into list
  foreach(generated_file ${generated_files})
    list(APPEND antlr4cpp_src_files_${antlr4cpp_project_namespace} ${generated_file})
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set_source_files_properties(
      ${generated_file}
      PROPERTIES
      COMPILE_FLAGS -Wno-overloaded-virtual
      )
    endif ()
  endforeach(generated_file)
  message(STATUS "Antlr4Cpp ${antlr4cpp_project_namespace} Generated: ${generated_files}")

  # export generated include directory
  set(antlr4cpp_include_dirs_${antlr4cpp_project_namespace} ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace})
  message(STATUS "Antlr4Cpp ${antlr4cpp_project_namespace} include: ${ANTLR4CPP_GENERATED_SRC_DIR}/${antlr4cpp_project_namespace}")

endmacro()
