#pragma once
#include <valarray>
#include <functional>

namespace frac {
template <typename U>
inline std::valarray<U> cross(const std::valarray<U>& lhs,
    const std::valarray<U>& rhs);

template <typename U>
inline void axis_rotate(const std::valarray<U>& input,
    const std::valarray<U>& axis, U degree, std::valarray<U>& res);
}

#include "linalg_helper.tpp"
