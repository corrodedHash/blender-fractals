#pragma once

template <typename U>
static std::valarray<U> cross(const std::valarray<U>& lhs,
    const std::valarray<U>& rhs)
{
    std::valarray<U> result = { 0, 0, 0 };
  result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
  result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
  result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
  return result;
}

template <typename U>
static inline void axis_rotate(const std::valarray<U>& input,
    const std::valarray<U>& axis, U degree, std::valarray<U>& res)
{
    static const U sqrt3_2 = static_cast<U>(0.5)*std::sqrt(static_cast<U>(3));
    static const U rad_degree_constant = static_cast<U>(4)*std::atan(static_cast<U>(1))/static_cast<U>(180);
  
    if (degree == static_cast<U>(90))
    {
        res[0] = axis[0]*axis[0]*input[0] + (axis[0]*axis[1]-axis[2])*input[1] + (axis[0]*axis[2]+axis[1])*input[2];
        res[1] = (axis[0]*axis[1]+axis[2])*input[0] + (axis[1]*axis[1])*input[1] + (axis[1]*axis[2]-axis[0])*input[2];
        res[2] = (axis[0]*axis[2]-axis[1])*input[0] + (axis[1]*axis[2]+axis[0])*input[1]+(axis[2]*axis[2])*input[2];
        return;
    }
    if (degree == static_cast<U>(-90))
    {
        res[0] = (axis[0]*axis[0])*input[0] + (axis[0]*axis[1]+axis[2])*input[1] + (axis[0]*axis[2]-axis[1])*input[2];
        res[1] = (axis[0]*axis[1]-axis[2])*input[0] + (axis[1]*axis[1])*input[1] + (axis[1]*axis[2]+axis[0])*input[2];
        res[2] = (axis[0]*axis[2]+axis[1])*input[0] + (axis[1]*axis[2]-axis[0])*input[1]+(axis[2]*axis[2])*input[2];
        return;
    }

	U c, s;
    auto abs_val = std::abs(degree);
    if (abs_val == static_cast<U>(60))
    {
        c = 0.5;
        s = std::copysign(sqrt3_2,degree);
    }
    else if (abs_val == static_cast<U>(120))
    {
        c = -0.5;
        s = std::copysign(sqrt3_2,degree);
    }
    else
    {
        c = std::cos(degree*rad_degree_constant);
        s = std::sin(degree*rad_degree_constant);
    }
    
    const U c1 = static_cast<U>(1)-c;
    res[0] = (c+axis[0]*axis[0]*c1)*input[0] + (axis[0]*axis[1]*c1-axis[2]*s)*input[1] + (axis[0]*axis[2]*c1+axis[1]*s)*input[2];
    res[1] = (axis[0]*axis[1]*c1+axis[2]*s)*input[0] + (c+axis[1]*axis[1]*c1)*input[1] + (axis[1]*axis[2]*c1-axis[0]*s)*input[2];
    res[2] = (axis[0]*axis[2]*c1-axis[1]*s)*input[0] + (axis[1]*axis[2]*c1+axis[0]*s)*input[1]+(c+axis[2]*axis[2]*c1)*input[2];
}
