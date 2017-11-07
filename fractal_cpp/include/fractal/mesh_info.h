#pragma once
#include "fractal/fractal.h"

#include <cstdint>
#include <algorithm>

template <typename U> struct mesh_info {
  mesh_info() = default;
  mesh_info(const Fractal<U>& other){
    vert_size = other.verts.size();
    verts = new U[other.verts.size()];

    edge_size = other.edges.size();
    edges = new std::size_t[other.edges.size()];

    face_vert_size = other.faces.face_verts.size();
    face_bound_size = other.faces.face_bounds.size();
    face_verts = new std::size_t[other.faces.face_verts.size()];
    face_bounds = new std::size_t[other.faces.face_bounds.size()];

    std::copy(std::begin(other.verts), std::end(other.verts), verts);
    std::copy(std::begin(other.edges), std::end(other.edges), edges);
    std::copy(std::begin(other.faces.face_verts), std::end(other.faces.face_verts),
              face_verts);
    std::copy(std::begin(other.faces.face_bounds), std::end(other.faces.face_bounds),
              face_bounds);
  } 
  U *verts;
  std::size_t *edges;
  std::size_t *face_verts;
  std::size_t *face_bounds;
  std::size_t vert_size, edge_size, face_vert_size, face_bound_size;
};
