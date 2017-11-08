add_library(lib_visitor OBJECT nonterminal.cpp)
add_dependencies(lib_visitor antlr4cpp antlr4cpp_generation_antlr)
set (LIB_SRC_FILES ${LIB_SRC_FILES} $<TARGET_OBJECTS:lib_visitor> PARENT_SCOPE)
