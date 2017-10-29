#pragma once

const double rad_degree_constant = (4. * std::atan(1.)) / 180.;

template <typename U>
static std::valarray<U> cross(const std::valarray<U> &lhs,
                              const std::valarray<U> &rhs) {
  std::valarray<U> result = {0, 0, 0};
  result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
  result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
  result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
  return result;
}

template <typename U>
static std::valarray<U> axis_rotate(const std::valarray<U> &input,
                                    const std::valarray<U> &axis, U degree) {
  return axis * (axis * input) +
         std::cos(degree * rad_degree_constant) *
             cross(cross(axis, input), axis) +
         std::sin(degree * rad_degree_constant) * cross(axis, input);
}
