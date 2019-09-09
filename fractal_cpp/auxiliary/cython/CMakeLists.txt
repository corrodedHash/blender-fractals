if (${PROJECT_NAME}_GENERATE_CYTHON)
  find_package(Cython REQUIRED)
  add_custom_command(OUTPUT fractalgen.cpp
    COMMAND ${CYTHON_EXECUTABLE} -3 --cplus -o ${CMAKE_CURRENT_BINARY_DIR}/fractalgen.cpp ${CMAKE_CURRENT_SOURCE_DIR}/fractalgen.pyx
  DEPENDS fractalgen.pyx)
endif()

add_library(aux_python_bridge OBJECT fractalgen.cpp)
set_target_properties(aux_python_bridge PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(aux_python_bridge PUBLIC GeneralConfig)
target_include_directories(aux_python_bridge PUBLIC ${Python_INCLUDE_DIRS})
