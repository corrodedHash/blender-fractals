add_library(lib_generator OBJECT fractalgen.cpp commandhandler.cpp)
add_dependencies(lib_generator antlr4cpp antlr4cpp_generation_antlr)
set (LIB_SRC_FILES ${LIB_SRC_FILES} $<TARGET_OBJECTS:lib_generator> PARENT_SCOPE)
