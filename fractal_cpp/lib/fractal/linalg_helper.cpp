#include "fractal/linalg_helper.h"

#include <array>
#include <valarray>

namespace frac {
std::valarray<FType>
cross(const std::valarray<FType>& lhs, const std::valarray<FType>& rhs) {
  std::valarray<FType> result = {0, 0, 0};
  result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
  result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
  result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
  return result;
}

void
axis_rotate(const std::valarray<::frac::FType>& input,
            const std::valarray<::frac::FType>& axis, ::frac::FType degree,
            std::valarray<::frac::FType>& res) {
  static const FType sqrt3_2 =
      static_cast<FType>(0.5) * std::sqrt(static_cast<FType>(3));
  static const FType rad_degree_constant = static_cast<FType>(4) *
                                           std::atan(static_cast<FType>(1)) /
                                           static_cast<FType>(180);
  std::array<FType, 3> tmp;

  if (degree == static_cast<FType>(90)) {
    tmp[0] = axis[0] * axis[0] * input[0] +
             (axis[0] * axis[1] - axis[2]) * input[1] +
             (axis[0] * axis[2] + axis[1]) * input[2];
    tmp[1] = (axis[0] * axis[1] + axis[2]) * input[0] +
             (axis[1] * axis[1]) * input[1] +
             (axis[1] * axis[2] - axis[0]) * input[2];
    tmp[2] = (axis[0] * axis[2] - axis[1]) * input[0] +
             (axis[1] * axis[2] + axis[0]) * input[1] +
             (axis[2] * axis[2]) * input[2];
    std::copy(std::begin(tmp), std::end(tmp), std::begin(res));
    return;
  }
  if (degree == static_cast<FType>(-90)) {
    tmp[0] = (axis[0] * axis[0]) * input[0] +
             (axis[0] * axis[1] + axis[2]) * input[1] +
             (axis[0] * axis[2] - axis[1]) * input[2];
    tmp[1] = (axis[0] * axis[1] - axis[2]) * input[0] +
             (axis[1] * axis[1]) * input[1] +
             (axis[1] * axis[2] + axis[0]) * input[2];
    tmp[2] = (axis[0] * axis[2] + axis[1]) * input[0] +
             (axis[1] * axis[2] - axis[0]) * input[1] +
             (axis[2] * axis[2]) * input[2];
    std::copy(std::begin(tmp), std::end(tmp), std::begin(res));
    return;
  }

  FType c, s;
  auto abs_val = std::abs(degree);
  if (abs_val == static_cast<FType>(60)) {
    c = 0.5;
    s = std::copysign(sqrt3_2, degree);
  } else if (abs_val == static_cast<FType>(120)) {
    c = -0.5;
    s = std::copysign(sqrt3_2, degree);
  } else {
    c = std::cos(degree * rad_degree_constant);
    s = std::sin(degree * rad_degree_constant);
  }

  const FType c1 = static_cast<FType>(1) - c;
  tmp[0] = (c + axis[0] * axis[0] * c1) * input[0] +
           (axis[0] * axis[1] * c1 - axis[2] * s) * input[1] +
           (axis[0] * axis[2] * c1 + axis[1] * s) * input[2];
  tmp[1] = (axis[0] * axis[1] * c1 + axis[2] * s) * input[0] +
           (c + axis[1] * axis[1] * c1) * input[1] +
           (axis[1] * axis[2] * c1 - axis[0] * s) * input[2];
  tmp[2] = (axis[0] * axis[2] * c1 - axis[1] * s) * input[0] +
           (axis[1] * axis[2] * c1 + axis[0] * s) * input[1] +
           (c + axis[2] * axis[2] * c1) * input[2];
  std::copy(std::begin(tmp), std::end(tmp), std::begin(res));
}
} // namespace frac
