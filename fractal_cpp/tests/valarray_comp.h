#pragma once
#include "master/config.h"
#include "catch.hpp"
#include <valarray>
#include <cmath>

inline std::string valtostring(const std::valarray<::frac::FType>& tos){
    std::ostringstream ss;
    ss << "(" << tos[0];
    for (int i = 1; i < tos.size(); ++i){
      ss << ", " << tos[i];
    }
    ss << ")";
    return ss.str();
}

class ValComp : public Catch::MatcherBase<std::valarray<::frac::FType>> {
  std::valarray<::frac::FType> tocompare;

  public:
  ValComp(std::valarray<::frac::FType> tocompare_)
      : tocompare(tocompare_)
  {
  }

  // Performs the test for this matcher
  bool match(const std::valarray<::frac::FType>& comparee) const override
  {
    if (tocompare.size() != comparee.size())
      return false;
    for (int i = 0; i < tocompare.size(); ++i)
      if (std::abs(tocompare[i] - comparee[i]) > 0.00001)
        return false;
    return true;
  }

  // Produces a string describing what this matcher does. It should
  // include any provided data (the begin/ end in this case) and
  // be written as if it were stating a fact (in the output it will be
  // preceded by the value under test).
  std::string describe() const override
  {
    std::ostringstream ss;
    ss << " is about equal to " << valtostring(tocompare);
    return ss.str();
  }
};
