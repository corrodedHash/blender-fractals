#pragma once

#include "master/config.h"

#include <array>
#include <memory>
#include <random>

namespace frac {
struct Terminal {
public:
  enum class TerminalType {
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

  Terminal() : ttype(Terminal::TerminalType::EMPTY) {}
  Terminal(TerminalType ttype_) : ttype(ttype_) {}
  bool operator==(const Terminal& other) const { return ttype == other.ttype; }
  bool operator!=(const Terminal& other) const { return not(*this == other); }
};
} // namespace frac
