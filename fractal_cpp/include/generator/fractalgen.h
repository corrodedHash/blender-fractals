#pragma once

#include "fractal/fractal.h"

#include <array>
#include <cstdint>
#include <stack>
#include <valarray>

#include "fractal/mesh_info.h"
#include "generator/fractaltimer.h"
#include "visitor/literal.h"

template <typename U>
class FractalGenTester;
template <typename U>
class FractalGen {
  friend FractalGenTester<U>;
  private:
  std::stack<std::valarray<U>> position_stack;
  std::stack<std::valarray<U>> rotation_stack;
  std::stack<std::valarray<U>> look_at_stack;
  std::stack<std::size_t> verts_stack;

  Fractal<U> fractal;

  bool moved = false;

  public:
  void move(U distance);
  void draw(U distance);
  void face(U distance);
  void rotate(const std::array<U, 3>& rotation);

  void push();
  void pop();
  void endface();

  FractalGen<U>()
  {
    position_stack.push({ 0, 0, 0 });
    rotation_stack.push({ 1, 0, 0 });
    look_at_stack.push({ 0, 1, 0 });
    verts_stack.push(0);
    fractal.add_vert(position_stack.top());
  }

  mesh_info<U> output() { return mesh_info<U>(fractal); };
};

mesh_info<double> generateMesh(const std::string& filename,
    unsigned int level);

#include "fractalgen_commands.tpp"
