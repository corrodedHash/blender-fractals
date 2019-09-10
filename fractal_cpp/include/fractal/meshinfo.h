#pragma once
#include "fractal/fractal.h"

#include <algorithm>
#include <cstdint>

namespace frac {
struct MeshInfo {
  MeshInfo() = default;
  MeshInfo(const Fractal& other) {
    vert_size = other.verts.size();
    verts = new FType[other.verts.size()];

    edge_size = other.edges.size();
    edges = new IType[other.edges.size()];

    face_vert_size = other.faces.face_verts.size();
    face_bound_size = other.faces.face_bounds.size();
    face_verts = new IType[other.faces.face_verts.size()];
    face_bounds = new IType[other.faces.face_bounds.size()];

    face_starts = new IType[other.faces.face_bounds.size()];
    face_totals = new IType[other.faces.face_bounds.size()];

    std::copy(std::begin(other.verts), std::end(other.verts), verts);
    std::copy(std::begin(other.edges), std::end(other.edges), edges);
    std::copy(std::begin(other.faces.face_verts),
              std::end(other.faces.face_verts), face_verts);
    std::copy(std::begin(other.faces.face_bounds),
              std::end(other.faces.face_bounds), face_bounds);
    if (other.faces.face_bounds.size() > 0) {
      face_starts[0] = 0;
      for (unsigned int i = 1; i < other.faces.face_bounds.size(); ++i) {
        face_starts[i] = face_bounds[i - 1];
      }
      face_totals[0] = face_bounds[0];
      for (unsigned int i = 1; i < other.faces.face_bounds.size(); ++i) {
        face_totals[i] = face_bounds[i] - face_bounds[i - 1];
      }
    }
  }

  // We dont want an automatic destructor, as this is supposed to be used and
  // cleaned up by python This function is just for testing
  void clean_up() {
    delete[] verts;
    delete[] edges;
    delete[] face_verts;
    delete[] face_bounds;
    delete[] face_starts;
    delete[] face_totals;
  }
  FType* verts;
  IType* edges;
  IType* face_verts;
  IType* face_bounds;
  IType* face_starts;
  IType* face_totals;
  IType vert_size, edge_size, face_vert_size, face_bound_size;
};
} // namespace frac
