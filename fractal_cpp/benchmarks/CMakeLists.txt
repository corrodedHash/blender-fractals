add_executable(benchmarks main.cpp whole.cpp)

add_dependencies(benchmarks googlebench)
target_include_directories(benchmarks PUBLIC ${GOOGLEBENCH_INCLUDE})
target_link_libraries(benchmarks libbenchmark.a pthread fractalgen)
