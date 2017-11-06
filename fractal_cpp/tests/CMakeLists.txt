add_library(tests OBJECT main.cpp)

set(TEST_SRC_FILES $<TARGET_OBJECTS:tests> PARENT_SCOPE)
