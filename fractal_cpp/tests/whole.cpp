#include "catch.hpp"
#include "generator/fractalgen.h"

TEST_CASE("whole"){
    generateFractal("/home/lukas/documents/coding/python/blender-fractals/examples/standard/sierpinski.txt", 10);
}
