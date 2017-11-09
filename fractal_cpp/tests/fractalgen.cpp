#include "catch.hpp"
#include "generator/fractalgen.h"

template <typename U>
class FractalGenTester {
  public:
  FractalGen<U> fractalgen;
  std::stack<std::valarray<U>>& get_pos() { return fractalgen.position_stack; };
  std::stack<std::valarray<U>>& get_rot() { return fractalgen.rotation_stack; };
  Fractal<U>& get_fractal() {return fractalgen.fractal;};
  //std::stack<std::valarray<U>>& get_look() { return look_at_stack; };
  //std::stack<std::size_t>& get_verts() { return verts_stack; };
};

TEST_CASE("sierpinsky")
{
  FractalGenTester<double> myfrac;
  REQUIRE(myfrac.get_pos().top()[0] == Approx(0));
  REQUIRE(myfrac.get_pos().top()[1] == Approx(0));
  REQUIRE(myfrac.get_pos().top()[2] == Approx(0));

  myfrac.fractalgen.rotate({-60, 0, 0});
  myfrac.fractalgen.draw(0.1);
  REQUIRE(myfrac.get_pos().top()[0] == Approx(0.05));
  REQUIRE(myfrac.get_pos().top()[1] == Approx(0));
  REQUIRE(myfrac.get_pos().top()[2] == Approx(0.086603));

  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.draw(0.1);
  REQUIRE(myfrac.get_pos().top()[0] == Approx(0.15));
  REQUIRE(myfrac.get_pos().top()[1] == Approx(0));
  REQUIRE(myfrac.get_pos().top()[2] == Approx(0.086603));

  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.draw(0.1);
  REQUIRE(myfrac.get_pos().top()[0] == Approx(0.2));
  REQUIRE(myfrac.get_pos().top()[1] == Approx(0));
  REQUIRE(myfrac.get_pos().top()[2] == Approx(0).margin(0.01));
}

TEST_CASE("flikflak"){
  FractalGenTester<double> myfrac;
  REQUIRE(myfrac.get_rot().top()[0] == 1);
  REQUIRE(myfrac.get_rot().top()[1] == 0);
  REQUIRE(myfrac.get_rot().top()[2] == 0);

  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({-60, 0, 0});
  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({-60, 0, 0});
  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({-60, 0, 0});

  REQUIRE(myfrac.get_rot().top()[0] == Approx(1));
  REQUIRE(myfrac.get_rot().top()[1] == 0);
  REQUIRE(myfrac.get_rot().top()[2] == Approx(0).margin(0.01));
}

TEST_CASE("circle rot"){
  FractalGenTester<double> myfrac;
  REQUIRE(myfrac.get_rot().top()[0] == 1);
  REQUIRE(myfrac.get_rot().top()[1] == 0);
  REQUIRE(myfrac.get_rot().top()[2] == 0);

  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({60, 0, 0});
  REQUIRE(myfrac.get_rot().top()[0] == Approx(-1));
  REQUIRE(myfrac.get_rot().top()[1] == 0);
  REQUIRE(myfrac.get_rot().top()[2] == Approx(0).margin(0.01));

  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({60, 0, 0});
  myfrac.fractalgen.rotate({60, 0, 0});
  REQUIRE(myfrac.get_rot().top()[0] == Approx(1));
  REQUIRE(myfrac.get_rot().top()[1] == 0);
  REQUIRE(myfrac.get_rot().top()[2] == Approx(0).margin(0.01));
}
