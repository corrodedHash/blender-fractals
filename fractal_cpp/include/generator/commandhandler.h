#pragma once
#include "generator/fractalgen.h"
#include "visitor/terminal.h"
#include <array>

namespace frac {
class CommandHandler {

  FractalGen& fractal;

  ::frac::FType rand(FType start, FType end);
  public:
  CommandHandler(FractalGen& fractal_): fractal(fractal_){};
  ::frac::FType random_number(const std::array<FType, 6>& values);

  std::array<FType, 3> random_vector(const std::array<FType, 6>& values);
  void handle(const Terminal& term);
};

}
