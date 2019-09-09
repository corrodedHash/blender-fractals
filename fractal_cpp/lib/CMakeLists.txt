add_library(Core STATIC $<TARGET_OBJECTS:aux_parsing>)

set_target_properties(Core PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_subdirectory(generator)
add_subdirectory(fractal)
add_subdirectory(visitor)

add_dependencies(Core antlr4cpp antlr4cpp_generation_antlr)

target_link_libraries(Core GeneralConfig)
target_link_libraries(Core antlr4-runtime)
target_link_libraries(Core aux_parsing)
