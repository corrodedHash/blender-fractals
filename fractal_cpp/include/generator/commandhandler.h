#pragma once
#include "generator/fractalgen.h"
#include "visitor/terminal.h"
#include <array>

class CommandHandler {

  FractalGen<double>& fractal;

  double rand(double start, double end);
  public:
  CommandHandler(FractalGen<double>& fractal_): fractal(fractal_){};
  double random_double(const std::array<double, 6>& values);

  std::array<double, 3> random_vector(const std::array<double, 6>& values);
  void handle(const Terminal& term);
};
