#pragma once
#include <vector>
#include <valarray>

#include "fractal/faces.h"

namespace frac {
struct Faces;
struct Fractal {
  std::vector<FType> verts;
  std::vector<IType> edges;
  Faces faces;

  void add_vert(const std::valarray<FType>& vert){
    verts.insert(std::end(verts), std::begin(vert),
                 std::end(vert));
  }
  std::size_t vert_count(){
    return verts.size() / 3;
  }
  void add_edge(IType v1, IType v2){
    edges.push_back(v1);
    edges.push_back(v2);
  }
};
}
