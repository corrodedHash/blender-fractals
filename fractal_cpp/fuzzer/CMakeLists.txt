add_executable(fuzzer main.cpp)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/corpus)  
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples)  
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/crashes)  

target_link_libraries(fuzzer lib_core ${CMAKE_CURRENT_SOURCE_DIR}/libclang_rt.fuzzer-x86_64.a pthread rt)

add_custom_target(fuzz ./fuzzer corpus examples crashes DEPENDS fuzzer) 
add_custom_command(OUTPUT default.profdata 
  COMMAND llvm-profdata merge -sparse default.profraw -o default.profdata 
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/default.profraw)
add_custom_target(fuzz_cov llvm-cov show fuzzer -instr-profile=default.profdata -format=html > default.html 
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/default.profdata) 
