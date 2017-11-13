#include "fractal/linalg_helper.h"
#include "master/config.h"
#include "valarray_comp.h"
#include <iostream>
#include <valarray>

struct rot_result {
  std::valarray<::frac::FType> rotee;
  std::valarray<::frac::FType> axis;
  ::frac::FType angle;
  std::valarray<::frac::FType> expected;
};

TEST_CASE("axis rotate")
{
  std::vector<rot_result> test_vector;
  test_vector.push_back({ { 1, 0, 0 }, { 0, 1, 0 }, 90, { 0, 0, -1 } });
  test_vector.push_back({ { 1, 0, 0 }, { 0, 1, 0 }, 180, { -1, 0, 0 } });
  test_vector.push_back({ { 1, 0, 0 }, { 0, 1, 0 }, 60, { 0.5, 0, -0.866025 } });
  test_vector.push_back({ { 1, 1, 0 }, { 0, 1, 0 }, 90, { 0, 1, -1 } });
  test_vector.push_back({ { 1, 1, 0 }, { 0, 0.7071067811865475, 0.7071067811865475 }, 50, { 0.101112, 1.363069, -0.363069 } });
  test_vector.push_back({ { 1, 1, 0 }, { 0.5773502691896258, 0.5773502691896258, 0.5773502691896258 }, 50, { 0.438653, 1.323205, 0.238142 } });

  std::valarray<::frac::FType> result{ 0, 0, 0 };
  for (const rot_result& cur_test : test_vector) {
    frac::axis_rotate(cur_test.rotee, cur_test.axis, cur_test.angle, result);
    CHECK_THAT(cur_test.expected, ValComp(result));
  }
}
