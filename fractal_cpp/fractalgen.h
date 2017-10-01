#pragma once
#ifndef FRACTALGEN_H
#define FRACTALGEN_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <stack>

#include <valarray>

#include "fractaltimer.h"
#include "literal.h"

template <typename U> struct mesh_info {
  U *verts;
  std::size_t *edges;
  std::size_t *face_verts;
  std::size_t *face_bounds;
  std::size_t vert_size, edge_size, face_vert_size, face_bound_size;
};

struct Faces {
  std::vector<std::size_t> face_verts;
  std::vector<std::size_t> face_bounds = {0};
  void new_face() {
    if (face_verts.size() > face_bounds.back()) {
      face_bounds.push_back(face_verts.size());
    }
  }
  void append_face_vert(std::size_t vert) { face_verts.push_back(vert); }
  bool last_face_empty(){
    return face_verts.size() < face_bounds.back();
  }
};
template <typename U> class FractalGen {
private:
  std::stack<std::valarray<U>> position_stack;
  std::stack<std::valarray<U>> rotation_stack;
  std::stack<std::valarray<U>> look_at_stack;
  std::stack<std::size_t> verts_stack;

  std::vector<U> verts;
  std::vector<std::size_t> edges;
  Faces faces;

  bool moved;

  void move(U distance);
  void draw(U distance);
  void face(U distance);
  void rotate(const std::array<U, 3> &rotation);

  void push();
  void pop();
  void endface();

public:
  FractalTimer ftime;
  FractalGen<U>() {
    position_stack.push({0, 0, 0});
    rotation_stack.push({1, 0, 0});
    look_at_stack.push({0, 1, 0});
    verts_stack.push(0);
  }

  mesh_info<U> output();

  void handle_command(const Terminal *term);
};

inline mesh_info<double> generateMesh(const std::string &filename,
                                      unsigned int level);

#endif /* end of include guard: FRACTALGEN_H */
