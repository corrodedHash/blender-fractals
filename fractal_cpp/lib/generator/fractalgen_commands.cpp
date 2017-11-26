#include "generator/fractalgen.h"
#include "fractal/linalg_helper.h"
#include "master/config.h"

namespace frac {
void FractalGen::move(FType distance)
{
  endface();
  moved = true;
  position_stack.top() += rotation_stack.top() * distance;
}

void FractalGen::draw(FType distance)
{
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

void FractalGen::face(FType distance)
{
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

void FractalGen::rotate(const std::array<FType, 3>& rotation)
{
  // Rotation around local y axis
  if (rotation[0] != 0) {
    frac::axis_rotate(rotation_stack.top(), look_at_stack.top(), rotation[0], rotation_stack.top());
  }
  // Rotation around local z axis
  if (rotation[1] != 0) {
    std::valarray<FType> rot_axis = frac::cross(rotation_stack.top(), look_at_stack.top());
    frac::axis_rotate(rotation_stack.top(), rot_axis, rotation[1], rotation_stack.top());
    frac::axis_rotate(look_at_stack.top(), rot_axis, rotation[1], look_at_stack.top());
  }
  if (rotation[2] != 0) {
    frac::axis_rotate(look_at_stack.top(), rotation_stack.top(), rotation[0], look_at_stack.top());
  }
}

void FractalGen::push()
{
  endface();
  position_stack.push(position_stack.top());
  rotation_stack.push(rotation_stack.top());
  look_at_stack.push(look_at_stack.top());
  verts_stack.push(verts_stack.top());
}
void FractalGen::pop()
{
  endface();
  if (rotation_stack.size() <= 1){
    throw std::runtime_error("Tried to pop empty stack");
  }
  position_stack.pop();
  rotation_stack.pop();
  look_at_stack.pop();
  verts_stack.pop();
}
void FractalGen::endface() { fractal.faces.new_face(); }
}
