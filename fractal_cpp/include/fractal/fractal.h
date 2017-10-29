#pragma once
#include <vector>
#include <valarray>

#include "fractal/faces.h"

class Faces;
template <typename U> struct Fractal {
  std::vector<U> verts;
  std::vector<std::size_t> edges;
  Faces faces;

  void add_vert(const std::valarray<U>& vert){
    verts.insert(std::end(verts), std::begin(vert),
                 std::end(vert));
  }
  std::size_t vert_count(){
    return verts.size() / 3;
  }
  void add_edge(std::size_t v1, std::size_t v2){
    edges.push_back(v1);
    edges.push_back(v2);
  }
};
