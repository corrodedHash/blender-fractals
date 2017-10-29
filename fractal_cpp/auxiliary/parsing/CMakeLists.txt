foreach(generated_file ${antlr4cpp_src_files_antlr})
  set_source_files_properties(${generated_file} PROPERTIES GENERATED TRUE)
endforeach(generated_file)

add_library(parsing OBJECT ${antlr4cpp_src_files_antlr})
add_dependencies(parsing antlr4cpp antlr4cpp_generation_antlr)
