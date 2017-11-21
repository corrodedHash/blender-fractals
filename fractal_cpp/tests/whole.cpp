#include "catch.hpp"
#include "generator/fractalgen.h"
#include "config.h"

TEST_CASE("whole"){
  auto x = frac::generateMesh(grammarpath + "/standard/sierpinski.txt", 10);
  x.clean_up();
}
