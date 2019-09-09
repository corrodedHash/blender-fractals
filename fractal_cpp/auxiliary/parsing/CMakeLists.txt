# Generate antlr files
include( ExternalAntlr4Cpp )

antlr4cpp_process_grammar(fractal_parse antlr
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemLexer.g4
  ${CMAKE_SOURCE_DIR}/auxiliary/parsing/lsystemParser.g4)
include_directories(${antlr4cpp_include_dirs_antlr})

foreach(generated_file ${antlr4cpp_src_files_antlr})
  set_source_files_properties(${generated_file} PROPERTIES GENERATED TRUE)
endforeach(generated_file)

add_library(aux_parsing OBJECT ${antlr4cpp_src_files_antlr})
target_link_directories(aux_parsing PUBLIC ${ANTLR4CPP_LIBS})
target_include_directories(aux_parsing PUBLIC ${antlr4cpp_include_dirs_antlr})
target_include_directories(aux_parsing PUBLIC ${ANTLR4CPP_INCLUDE_DIRS})

add_dependencies(aux_parsing antlr4cpp antlr4cpp_generation_antlr)
set_target_properties(aux_parsing PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
