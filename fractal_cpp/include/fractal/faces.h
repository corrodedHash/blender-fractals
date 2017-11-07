#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

struct Faces {
  std::vector<std::size_t> face_verts{};
  std::vector<std::size_t> face_bounds{};
  void new_face()
  {
    if (not last_face_empty()) {
      face_bounds.push_back(face_verts.size());
    }
  }
  void append_face_vert(std::size_t vert) { face_verts.push_back(vert); }
  bool last_face_empty()
  {
    if (face_bounds.empty()) {
      return face_verts.empty();
    } else {
      return face_verts.size() <= face_bounds.back();
    }
  }
};
