#include "catch.hpp"
#include <valarray>

class ValComp : public Catch::MatcherBase<std::valarray<double>> {
  std::valarray<double> tocompare;

  public:
  ValComp(std::valarray<double> tocompare_)
      : tocompare(tocompare_)
  {
  }

  // Performs the test for this matcher
  bool match(const std::valarray<double>& comparee) const override
  {
    if (tocompare.size() != comparee.size())
      return false;
    for (int i = 0; i < tocompare.size(); ++i)
      if (tocompare[i] - comparee[i] > 0.00001)
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
    ss << " is about equal to (" << tocompare[0];
    for (int i = 1; i < tocompare.size(); ++i){
      ss << ", " << tocompare[i];
    }
    ss << ")";
    return ss.str();
  }
};
