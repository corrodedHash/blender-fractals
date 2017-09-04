#pragma once
#ifndef FRACTALGEN_H
#define FRACTALGEN_H

#include <algorithm>
#include <array>
#include <cstdint>
#include <stack>
#include <chrono>
#include <iostream>

#include <valarray>

#include "literal.h"

template <typename U> struct mesh_info {
  U *verts;
  std::size_t* edges, *faces;
  std::size_t vert_size, edge_size, face_size;
};

class FractalTimer {
  std::chrono::steady_clock::time_point itcom_begin;

  std::chrono::steady_clock::time_point com_begin;
  public:

  long it_diff = 0;
  long com_diff = 0;

  long rot_diff = 0;
  long move_diff = 0;
  long draw_diff = 0;
  long face_diff = 0;
  long endf_diff = 0;
  long push_diff = 0;
  long pop_diff = 0;

  void itcom_start(){
    itcom_begin = std::chrono::steady_clock::now();
  }
  long itcom_end(){
   return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - itcom_begin).count();
  }

  void com_start(){
    com_begin = std::chrono::steady_clock::now();
  }
  long com_end(){
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - com_begin).count();
  }

  void print(){
  std::cout << "Rotation: " << rot_diff << "\n";
  std::cout << "Move: " << move_diff << "\n";
  std::cout << "Draw: " << draw_diff<< "\n";
  std::cout << "Face: " << face_diff << "\n";
  std::cout << "Endface: " << endf_diff << "\n";
  std::cout << "Push: " << push_diff << "\n";
  std::cout << "Pop: " << pop_diff << "\n";
  std::cout << "Total: " << rot_diff + move_diff + draw_diff + face_diff + endf_diff +push_diff + pop_diff<< std::endl;
  std::cout << "iterate: " << it_diff << "\n";
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
  std::vector<std::size_t> faces;

  bool moved;

  void move(U distance);
  void draw(U distance);
  void face(U distance);
  void rotate(const std::array<U, 3>& rotation);

  void push();
  void pop();
  void endface();

public:
  FractalTimer ftime;
  FractalGen<U>(){
    position_stack.push({0, 0, 0});
    rotation_stack.push({1, 0, 0});
    look_at_stack.push({0, 1, 0});
    verts_stack.push(0);
  }

  mesh_info<U> output();

  void handle_command(const Terminal* term);
};

mesh_info<double> generateMesh(const std::string& filename, unsigned int level);

#endif /* end of include guard: FRACTALGEN_H */
