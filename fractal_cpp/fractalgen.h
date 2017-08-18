#pragma once
#ifndef FRACTALGEN_H
#define FRACTALGEN_H

#include <cstdint>
#include <algorithm>


template <typename U>
struct dynarr {
  U* raw;
  std::size_t count;
  std::size_t capacity;

  void push_back(const U& _pushback){
    if (count == capacity){
      resize(capacity * 2);
    }
    raw[count] = _pushback;
    ++count;
  }

  void resize(std::size_t new_size){
    assert(new_size > capacity);
    U* new_raw = new U[new_size];
    std::copy(raw, raw + count, new_raw);
    delete[] raw;
    raw = new_raw;
    capacity = new_size;
  }

};

class fractalgen {
private:
  dynarr<std::uint64_t> verts;
  dynarr<std::uint64_t> edges;
  dynarr<std::uint64_t> faces;

public:
  dynarr<std::uint64_t> 
};

#endif /* end of include guard: FRACTALGEN_H */
