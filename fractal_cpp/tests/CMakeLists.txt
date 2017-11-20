add_executable(testing main.cpp fractalgen.cpp whole.cpp linalg.cpp random.cpp)

target_link_libraries(testing lib_core)

add_test(NAME main_test COMMAND testing)
