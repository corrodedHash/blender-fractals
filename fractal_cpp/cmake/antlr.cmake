include( "${CMAKE_SOURCE_DIR}/cmake/ExternalAntlr4Cpp.cmake" )
include_directories(${ANTLR4CPP_INCLUDE_DIRS})
link_directories( ${ANTLR4CPP_LIBS} )
antlr4cpp_process_grammar(fractal_parse antlr
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemLexer.g4
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemParser.g4)
include_directories(${antlr4cpp_include_dirs_antlr})
