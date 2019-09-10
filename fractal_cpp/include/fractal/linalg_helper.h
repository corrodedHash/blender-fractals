#pragma once
#include "master/config.h"

#include <valarray>

namespace frac {
std::valarray<FType>
cross(const std::valarray<FType>& lhs, const std::valarray<FType>& rhs);

void axis_rotate(const std::valarray<::frac::FType>& input,
                 const std::valarray<::frac::FType>& axis, ::frac::FType degree,
                 std::valarray<::frac::FType>& res);
} // namespace frac
