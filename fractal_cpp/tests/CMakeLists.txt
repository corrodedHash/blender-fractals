add_executable(testing main.cpp fractalgen.cpp whole.cpp linalg.cpp random.cpp)

target_link_libraries(testing corelib)

add_test(NAME main_test COMMAND testing)
