add_custom_command(OUTPUT fractalgen.cpp
  COMMAND ${CYTHON_EXECUTABLE} -3 --cplus -o ${CMAKE_CURRENT_BINARY_DIR}/fractalgen.cpp ${CMAKE_CURRENT_SOURCE_DIR}/fractalgen.pyx
DEPENDS fractalgen.pyx)

add_library(python_bridge OBJECT fractalgen.cpp)
target_include_directories(python_bridge PUBLIC /usr/include/python3.6m)

