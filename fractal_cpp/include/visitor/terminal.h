#pragma once

#include <array>

struct Terminal {
  public:
  enum TerminalType {
    ROTATE_TERM,
    MOVE_TERM,
    DRAW_TERM,
    FACE_TERM,
    ENDFACE_TERM,
    PUSH_TERM,
    POP_TERM,
    EMPTY
  };

  std::array<double, 6> values{};
  TerminalType ttype;

  public:
  Terminal(TerminalType _ttype)
      : ttype(_ttype)
  {}
  bool operator==(const Terminal& other) const{
    return ttype == other.ttype;
  }
  bool operator!=(const Terminal& other) const{
    return not(*this == other);
  }
};
