if (FRAC_GENERATE_CYTHON)
  # Heres to hoping that the generated file takes precedence
  add_custom_command(OUTPUT fractalgen.cpp
    COMMAND ${CYTHON_EXECUTABLE} -3 --cplus -o ${CMAKE_CURRENT_BINARY_DIR}/fractalgen.cpp ${CMAKE_CURRENT_SOURCE_DIR}/fractalgen.pyx
  DEPENDS fractalgen.pyx)
endif()

add_library(aux_python_bridge OBJECT fractalgen.cpp)
target_include_directories(aux_python_bridge PUBLIC ${PYTHON_INCLUDE_DIRS})

