add_library(lib_generator OBJECT fractalgen.cpp)
set (LIB_SRC_FILES ${LIB_SRC_FILES} $<TARGET_OBJECTS:lib_generator> PARENT_SCOPE)
