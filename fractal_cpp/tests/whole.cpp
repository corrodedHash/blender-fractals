#include "catch.hpp"
#include "generator/fractalgen.h"

TEST_CASE("whole"){
  auto x = frac::generateMesh("/home/lukas/documents/coding/python/blender-fractals/examples/standard/sierpinski.txt", 10);
  x.clean_up();
}
