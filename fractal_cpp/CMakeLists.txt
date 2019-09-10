project(blender-fractals LANGUAGES CXX DESCRIPTION "C++ backbone to the fractal plugin")
cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_CXX_STANDARD 17)


# Set compiler flags
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-local" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include( "common" NO_POLICY_SCOPE)

set(${PROJECT_NAME}_GENERATE_CYTHON ON CACHE BOOL "Generate the cython from the .pyx file, otherwise supply auxiliary/cython/fractalgen.cpp")
set(${PROJECT_NAME}_ENABLE_PYTHON ON CACHE BOOL "Generate the python module")

if (${PROJECT_NAME}_ENABLE_PYTHON)
  find_package(Python COMPONENTS Development REQUIRED)
endif()

add_subdirectory(lib)
add_subdirectory(auxiliary)

# Compile main output

if (${PROJECT_NAME}_ENABLE_PYTHON)
  add_library(fractalgen SHARED)

  target_link_libraries(fractalgen PRIVATE aux_python_bridge)
  target_link_libraries(fractalgen PRIVATE Core)
  target_link_libraries(fractalgen PRIVATE Python::Python )
  target_link_libraries(fractalgen PRIVATE GeneralConfig)

  set_target_properties(fractalgen PROPERTIES PREFIX "")
  set_target_properties(fractalgen PROPERTIES OUTPUT_NAME "fractalgen")
endif()
