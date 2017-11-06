set(ANTLR4CPP_JAR_LOCATION ${CMAKE_BINARY_DIR}/antlr-complete.jar)
execute_process(COMMAND curl http://www.antlr.org/download/antlr-4.7-complete.jar --output ${ANTLR4CPP_JAR_LOCATION})
include( "${CMAKE_SOURCE_DIR}/cmake/ExternalAntlr4Cpp.cmake" )
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories( ${ANTLR4CPP_LIBS} )
antlr4cpp_process_grammar(fractal_parse antlr
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemLexer.g4
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemParser.g4)
include_directories(${antlr4cpp_include_dirs_antlr})
