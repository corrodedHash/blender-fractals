add_library(lib_fractal OBJECT linalg_helper.cpp)
set (LIB_SRC_FILES ${LIB_SRC_FILES} $<TARGET_OBJECTS:lib_fractal> PARENT_SCOPE)
