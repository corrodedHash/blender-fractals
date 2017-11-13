#include "generator/fractalgen.h"
#include "catch.hpp"
#include "valarray_comp.h"

class FractalGenTester {
  public:
  frac::FractalGen fractalgen;
  std::stack<std::valarray<::frac::FType>>& get_pos() { return fractalgen.position_stack; };
  std::stack<std::valarray<::frac::FType>>& get_rot() { return fractalgen.rotation_stack; };
  std::stack<std::valarray<::frac::FType>>& get_look() { return fractalgen.look_at_stack; };
  frac::Fractal& get_fractal() { return fractalgen.fractal; };
  //std::stack<std::size_t>& get_verts() { return verts_stack; };
};

TEST_CASE("sierpinsky")
{
  FractalGenTester myfrac;
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 0, 0 }), ValComp(myfrac.get_pos().top()));

  myfrac.fractalgen.rotate({ -60, 0, 0 });
  myfrac.fractalgen.draw(0.1);
  CHECK_THAT(std::valarray<::frac::FType>({ 0.05, 0, 0.086603 }), ValComp(myfrac.get_pos().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.draw(0.1);
  CHECK_THAT(std::valarray<::frac::FType>({ 0.15, 0, 0.086603 }), ValComp(myfrac.get_pos().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.draw(0.1);
  CHECK_THAT(std::valarray<::frac::FType>({ 0.2, 0, 0 }), ValComp(myfrac.get_pos().top()));
}

TEST_CASE("flikflak")
{
  FractalGenTester myfrac;
  CHECK_THAT(std::valarray<::frac::FType>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ -60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ -60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ -60, 0, 0 });

  CHECK_THAT(std::valarray<::frac::FType>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));
}

TEST_CASE("circle rot")
{
  FractalGenTester myfrac;
  CHECK_THAT(std::valarray<::frac::FType>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  CHECK_THAT(std::valarray<::frac::FType>({ 0.5, 0, -0.866025 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  CHECK_THAT(std::valarray<::frac::FType>({ -0.5, 0, -0.866025 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));
  myfrac.fractalgen.rotate({ 60, 0, 0 });

  CHECK_THAT(std::valarray<::frac::FType>({ -1, 0, 0 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  CHECK_THAT(std::valarray<::frac::FType>({ -0.5, 0, 0.866025 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  CHECK_THAT(std::valarray<::frac::FType>({ 0.5, 0, 0.866025 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));
  myfrac.fractalgen.rotate({ 60, 0, 0 });

  CHECK_THAT(std::valarray<::frac::FType>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));
  CHECK_THAT(std::valarray<::frac::FType>({ 0, 1, 0 }), ValComp(myfrac.get_look().top()));
}
