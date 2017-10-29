#pragma once
#include <vector>
#include <cstdint>

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
