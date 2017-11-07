add_library(fractalgen SHARED ${LIB_SRC_FILES} $<TARGET_OBJECTS:python_bridge> $<TARGET_OBJECTS:parsing>)

target_link_libraries(fractalgen python3.6m libantlr4-runtime.a)

add_dependencies(fractalgen antlr4cpp_generation_antlr)

target_compile_options(fractalgen PUBLIC -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g
  -fwrapv -O3 -Wall -march=x86-64 -mtune=generic -O2 -pipe
  -fstack-protector-strong -fno-plt)

set_target_properties(fractalgen PROPERTIES PREFIX "")
set_target_properties(fractalgen PROPERTIES OUTPUT_NAME "fractalgen")
