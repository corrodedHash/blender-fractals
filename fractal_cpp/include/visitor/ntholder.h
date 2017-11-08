#pragma once

#include <vector>
#include <cstdint>

#include "visitor/terminal.h"

class NonTerminal;
class NTHolder {
  public:
  std::vector<NonTerminal*> list_NT;
  std::vector<Terminal> list_T;

  bool isTerminal(std::size_t index) const { return not(list_NT[index]); }

  void appendHolder(const NTHolder& nth)
  {
    list_NT.insert(std::end(list_NT), std::begin(nth.list_NT),
        std::end(nth.list_NT));
    list_T.insert(std::end(list_T), std::begin(nth.list_T),
        std::end(nth.list_T));
    assert(nth.list_NT.size() == nth.list_T.size());
  }

  void appendNT(NonTerminal* nt)
  {
    list_NT.push_back(nt);
    list_T.push_back(Terminal(Terminal::EMPTY));
  }
  void appendT(Terminal&& t)
  {
    list_NT.push_back(nullptr);
    list_T.push_back(t);
  }

  std::size_t size() const
  {
    assert(list_NT.size() == list_T.size());
    return list_NT.size();
  }

  bool operator==(const NTHolder& other) const{
    return list_NT == other.list_NT and list_T == other.list_T;
  }
  bool operator!=(const NTHolder& other) const{
    return not(*this == other);
  }
};
