add_executable(benchmarks main.cpp whole.cpp)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_dependencies(benchmarks googlebench)
target_include_directories(benchmarks PRIVATE ${GOOGLEBENCH_INCLUDE} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(benchmarks libbenchmark.a pthread fractalgen)
