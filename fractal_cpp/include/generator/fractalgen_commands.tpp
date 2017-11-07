#pragma once
#include "fractal/linalg_helper.h"

template <typename U> void FractalGen<U>::move(U distance) {
  endface();
  moved = true;
  position_stack.top() += rotation_stack.top() * distance;
}

template <typename U> void FractalGen<U>::draw(U distance) {
  endface();
  if (moved) {
    moved = false;
    fractal.add_vert(position_stack.top());
    verts_stack.top() = fractal.vert_count() - 1;
  }
  position_stack.top() += (rotation_stack.top() * distance);

  fractal.add_vert(position_stack.top());
  fractal.add_edge(verts_stack.top(), fractal.vert_count() - 1);
  verts_stack.top() = fractal.vert_count() - 1;
}

template <typename U> void FractalGen<U>::face(U distance) {
  if (moved) {
    moved = false;
    fractal.add_vert(position_stack.top());
    verts_stack.top() = fractal.vert_count() - 1;
    fractal.faces.append_face_vert(verts_stack.top());
  } else if (fractal.faces.last_face_empty()) {
    fractal.faces.append_face_vert(verts_stack.top());
  }
  position_stack.top() += (rotation_stack.top() * distance);

  fractal.add_vert(position_stack.top());
  verts_stack.top() = fractal.vert_count() - 1;
  fractal.faces.append_face_vert(verts_stack.top());
}

template <typename U>
void FractalGen<U>::rotate(const std::array<U, 3> &rotation) {
  // Rotation around local y axis
  if (rotation[0] != 0) {
    rotation_stack.top() =
        axis_rotate(rotation_stack.top(), look_at_stack.top(), rotation[0]);
  }
  // Rotation around local z axis
  if (rotation[1] != 0) {
    std::valarray<U> rot_axis =
        cross(rotation_stack.top(), look_at_stack.top());
    rotation_stack.top() =
        axis_rotate(rotation_stack.top(), rot_axis, rotation[1]);
    look_at_stack.top() =
        axis_rotate(look_at_stack.top(), rot_axis, rotation[1]);
  }
}

template <typename U> void FractalGen<U>::push() {
  endface();
  position_stack.push(position_stack.top());
  rotation_stack.push(rotation_stack.top());
  look_at_stack.push(look_at_stack.top());
  verts_stack.push(verts_stack.top());
}
template <typename U> void FractalGen<U>::pop() {
  endface();
  position_stack.pop();
  rotation_stack.pop();
  look_at_stack.pop();
  verts_stack.pop();
}
template <typename U> void FractalGen<U>::endface() { fractal.faces.new_face(); }

