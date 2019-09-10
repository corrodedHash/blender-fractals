#pragma once

#include "fractal/fractal.h"
#include "fractal/meshinfo.h"
#include "generator/fractaltimer.h"
#include "visitor/literal.h"

#include <array>
#include <cstdint>
#include <stack>
#include <valarray>

class FractalGenTester;
namespace frac {
class FractalGen {
  friend ::FractalGenTester;

private:
  std::stack<std::valarray<FType>> position_stack;
  std::stack<std::valarray<FType>> rotation_stack;
  std::stack<std::valarray<FType>> look_at_stack;
  std::stack<IType> verts_stack;

  Fractal fractal;

  bool moved = false;

public:
  void move(FType distance);
  void draw(FType distance);
  void face(FType distance);
  void rotate(const std::array<FType, 3>& rotation);

  void push();
  void pop();
  void endface();

  FractalGen() {
    position_stack.push({0, 0, 0});
    rotation_stack.push({1, 0, 0});
    look_at_stack.push({0, 1, 0});
    verts_stack.push(0);
    fractal.add_vert(position_stack.top());
  }

  MeshInfo output() { return MeshInfo(fractal); };
};

FractalGen generateFractal(const std::string& filename, unsigned int level);

FractalGen generateFractal(const char data[], size_t size, unsigned int level);

MeshInfo generateMesh(const std::string& filename, unsigned int level);

} // namespace frac
