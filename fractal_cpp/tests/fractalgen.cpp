#include "generator/fractalgen.h"
#include "catch.hpp"
#include "valarray_comp.h"

template <typename U>
class FractalGenTester {
  public:
  frac::FractalGen<U> fractalgen;
  std::stack<std::valarray<U>>& get_pos() { return fractalgen.position_stack; };
  std::stack<std::valarray<U>>& get_rot() { return fractalgen.rotation_stack; };
  frac::Fractal<U>& get_fractal() { return fractalgen.fractal; };
  //std::stack<std::valarray<U>>& get_look() { return look_at_stack; };
  //std::stack<std::size_t>& get_verts() { return verts_stack; };
};

TEST_CASE("sierpinsky")
{
  FractalGenTester<double> myfrac;
  CHECK_THAT(std::valarray<double>({ 0, 0, 0 }), ValComp(myfrac.get_pos().top()));

  myfrac.fractalgen.rotate({ -60, 0, 0 });
  myfrac.fractalgen.draw(0.1);
  CHECK_THAT(std::valarray<double>({ 0.05, 0, 0.086603 }), ValComp(myfrac.get_pos().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.draw(0.1);
  CHECK_THAT(std::valarray<double>({ 0.15, 0, 0.086603 }), ValComp(myfrac.get_pos().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.draw(0.1);
  CHECK_THAT(std::valarray<double>({ 0.2, 0, 0 }), ValComp(myfrac.get_pos().top()));
}

TEST_CASE("flikflak")
{
  FractalGenTester<double> myfrac;
  CHECK_THAT(std::valarray<double>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ -60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ -60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ -60, 0, 0 });

  CHECK_THAT(std::valarray<double>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));
}

TEST_CASE("circle rot")
{
  FractalGenTester<double> myfrac;
  CHECK_THAT(std::valarray<double>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });

  CHECK_THAT(std::valarray<double>({ -1, 0, 0 }), ValComp(myfrac.get_rot().top()));

  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });
  myfrac.fractalgen.rotate({ 60, 0, 0 });

  CHECK_THAT(std::valarray<double>({ 1, 0, 0 }), ValComp(myfrac.get_rot().top()));
}
