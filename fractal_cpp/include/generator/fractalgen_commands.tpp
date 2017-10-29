#pragma once
#include "fractal/linalg_helper.h"

template <typename U> void FractalGen<U>::move(U distance) {
  endface();
  moved = true;
  position_stack.top() = rotation_stack.top() * distance;
}

template <typename U> void FractalGen<U>::draw(U distance) {
  endface();
  if (moved) {
    moved = false;
    fractal.add_vert(position_stack.top());
    verts_stack.top() = fractal.vert_count();
  }
  position_stack.top() += (rotation_stack.top() * distance);

  fractal.add_vert(position_stack.top());
  fractal.add_edge(verts_stack.top() - 1, fractal.vert_count() - 1);
  verts_stack.top() = fractal.vert_count();
}

template <typename U> void FractalGen<U>::face(U distance) {
  if (moved) {
    moved = false;
    fractal.add_vert(position_stack.top());
    verts_stack.top() = fractal.vert_count();
  }
  position_stack.top() += (rotation_stack.top() * distance);

  fractal.add_vert(position_stack.top());
  if (fractal.faces.last_face_empty()) {
    fractal.faces.append_face_vert(verts_stack.top() - 1);
  }
  fractal.faces.append_face_vert(fractal.vert_count() - 1);
  verts_stack.top() = fractal.vert_count();
}

template <typename U>
void FractalGen<U>::rotate(const std::array<U, 3> &rotation) {
  if (rotation[0] != 0) {
    rotation_stack.top() =
        axis_rotate(rotation_stack.top(), look_at_stack.top(), rotation[0]);
  }
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

template <typename U> void FractalGen<U>::handle_command(const Terminal *term) {
  switch (term->ttype) {
  case Terminal::ROTATE_TERM:
    this->rotate(term->values);
    break;
  case Terminal::MOVE_TERM:
    this->move(term->values[0]);
    break;
  case Terminal::DRAW_TERM:
    this->draw(term->values[0]);
    break;
  case Terminal::FACE_TERM:
    this->face(term->values[0]);
    break;
  case Terminal::ENDFACE_TERM:
    this->endface();
    break;
  case Terminal::PUSH_TERM:
    this->push();
    break;
  case Terminal::POP_TERM:
    this->pop();
    break;
  case Terminal::EMPTY:
    throw std::runtime_error("Iterated to empty terminal");
  default:
    throw std::runtime_error("Unknown terminal");
  }
}
