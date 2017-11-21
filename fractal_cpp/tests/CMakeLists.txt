add_executable(testing main.cpp fractalgen.cpp whole.cpp linalg.cpp random.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

target_link_libraries(testing lib_core)
target_include_directories(testing PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME main_test COMMAND testing)
