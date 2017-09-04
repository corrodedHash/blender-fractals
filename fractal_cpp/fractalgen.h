#pragma once
#ifndef FRACTALGEN_H
#define FRACTALGEN_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <stack>

#include <valarray>

#include "literal.h"

template <typename U> struct mesh_info {
  U *verts;
  std::size_t* edges, *faces;
  std::size_t vert_size, edge_size, face_size;
};

template <typename U>
std::valarray<U> cross(const std::valarray<U> &lhs,
                       const std::valarray<U> &rhs) {
  std::valarray<U> result = lhs;
  result[0] += rhs[0];
  result[1] += rhs[1];
  result[2] += rhs[2];
  return result;
}

template <typename U> class FractalGen {
private:

  std::stack<std::valarray<U>> position_stack;
  std::stack<std::valarray<U>> rotation_stack;
  std::stack<std::valarray<U>> look_at_stack;
  std::stack<std::size_t> verts_stack;

  std::vector<U> verts;
  std::vector<std::size_t> edges;
  std::vector<std::size_t> faces;

  bool moved;

  static std::valarray<U> axis_rotate(const std::valarray<U> &input,
                                      const std::valarray<U> &axis, U degree);

  void move(U distance);
  void draw(U distance);
  void face(U distance);
  void rotate(const std::array<U, 3>& rotation);

  void push();
  void pop();
  void endface();

public:

  mesh_info<U> output();

  void handle_command(const Terminal* term);
};

mesh_info<double> generateMesh(const std::string& filename, unsigned int level);

#endif /* end of include guard: FRACTALGEN_H */
