add_library(lib_visitor OBJECT literal.cpp)
set (LIB_SRC_FILES ${LIB_SRC_FILES} $<TARGET_OBJECTS:lib_visitor> PARENT_SCOPE)
