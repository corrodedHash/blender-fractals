add_library(tests OBJECT main.cpp fractalgen.cpp)

set(TEST_SRC_FILES $<TARGET_OBJECTS:tests> PARENT_SCOPE)
