add_subdirectory(fractal)
add_subdirectory(generator)
add_subdirectory(visitor)

add_library(lib_core STATIC $<TARGET_OBJECTS:aux_parsing> ${LIB_SRC_FILES})

target_link_libraries(lib_core libantlr4-runtime.a)
add_dependencies(lib_core antlr4cpp)
