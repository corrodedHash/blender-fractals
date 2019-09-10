#pragma once
#include "generator/fractalgen.h"
#include "visitor/terminal.h"

#include <array>

namespace frac {
struct RandomSuite {
  std::random_device rd;
  std::mt19937 mt = std::mt19937(rd());
  std::uniform_real_distribution<double> dist =
      std::uniform_real_distribution<double>(1.0, 10.0);
  ::frac::FType rand(FType start, FType end);
};
class CommandHandler {

  FractalGen& fractal;
  RandomSuite rndm;

  ::frac::FType random_number(const std::array<FType, 6>& values);
  std::array<FType, 3> random_vector(const std::array<FType, 6>& values);

public:
  CommandHandler(FractalGen& fractal_) : fractal(fractal_){};

  void handle(const Terminal& term);
};

} // namespace frac
