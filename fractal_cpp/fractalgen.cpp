#include "fractalgen.h"

#include <cmath>

const double rad_degree_constant = (4. * std::atan(1.)) / 180.;

template <typename U>
std::valarray<U> FractalGen<U>::axis_rotate(const std::valarray<U> &input,
                                            const std::valarray<U> &axis,
                                            U degree) {
  return input * (input * axis) +
         std::cos(degree * rad_degree_constant) *
             cross(cross(input, axis), input) +
         std::sin(degree * rad_degree_constant) * cross(input, axis);
}

template <typename U> void FractalGen<U>::move(U distance) {
  moved = true;
  position_stack.top = rotation_stack.top * distance;
}

template <typename U> void FractalGen<U>::draw(U distance) {
  if (moved) {
    moved = false;
    verts.insert(std::begin(verts), std::begin(position_stack.top()),
                 std::end(position_stack.top()));
    verts_stack.top() = verts.size() / 3;
  }
  position_stack.top() += (rotation_stack.top() * distance);

  verts.insert(std::begin(verts), std::begin(position_stack.top()),
               std::end(position_stack.top()));
  edges.push_back(verts_stack.top());
  edges.push_back(verts.size() / 3);
}

template <typename U> void FractalGen<U>::face(U distance){}
template <typename U> void FractalGen<U>::rotate(std::array<U, 3> rotation){}

template <typename U> void FractalGen<U>::push(){}
template <typename U> void FractalGen<U>::pop(){}
template <typename U> void FractalGen<U>::endface(){}

mesh_info<std::uint64_t> generateMesh() {}
