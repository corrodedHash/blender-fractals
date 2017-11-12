#pragma once
#include <valarray>
#include <functional>

namespace frac {
template <typename U>
inline std::valarray<U> cross(const std::valarray<U>& lhs,
    const std::valarray<U>& rhs);

template <typename U>
inline void axis_rotate_opt(const std::valarray<U>& input,
    const std::valarray<U>& axis, U degree, std::valarray<U>& res);

template <typename U>
inline void axis_rotate_bad(const std::valarray<U>& input,
    const std::valarray<U>& axis, U degree, std::valarray<U>& res);

inline std::function<void(const std::valarray<double>&, const std::valarray<double>&, double, std::valarray<double>&)> axis_rotate = axis_rotate_opt<double>;
}

#include "linalg_helper.tpp"
