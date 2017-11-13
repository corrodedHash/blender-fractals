#pragma once
#include "master/config.h"
#include <cstdint>
#include <iostream>
#include <vector>

namespace frac {
struct Faces {
  std::vector<IType> face_verts{};
  std::vector<IType> face_bounds{};
  void new_face()
  {
    if (not last_face_empty()) {
      face_bounds.push_back(face_verts.size());
    }
  }
  void append_face_vert(IType vert) { face_verts.push_back(vert); }
  bool last_face_empty()
  {
    if (face_bounds.empty()) {
      return face_verts.empty();
    } else {
      return face_verts.size() <= face_bounds.back();
    }
  }
};
}
