#include "catch.hpp"
#include "generator/commandhandler.h"
#include "master/config.h"

TEST_CASE("random"){
  ::frac::RandomSuite rndm;
  for (int i = 0; i < 10; ++i){
    for (int j = 1; j < 10; ++j){
      auto x = rndm.rand(i, i + j);
      REQUIRE(x <= i + j);
      REQUIRE(x >= i);
    }
  }
}
