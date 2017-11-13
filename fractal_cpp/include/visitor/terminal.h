#pragma once

#include "master/config.h"
#include <array>

namespace frac {
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

  std::array<::frac::FType, 6> values{};
  TerminalType ttype;

  public:
  Terminal(TerminalType _ttype)
      : ttype(_ttype)
  {
  }
  bool operator==(const Terminal& other) const
  {
    return ttype == other.ttype;
  }
  bool operator!=(const Terminal& other) const
  {
    return not(*this == other);
  }
};
}
