#include "generator/commandhandler.h"
#include <cstdlib>

::frac::FType (::frac::RandomSuite::rand)(::frac::FType start, ::frac::FType end)
{
  if (start == end){
    return start;
  }
  return dist(mt, std::uniform_real_distribution<double>::param_type(start, end));
}

::frac::FType (::frac::CommandHandler::random_number)(const std::array<::frac::FType, 6>& values)
{
  return rndm.rand(values[0], values[1]);
}

std::array<::frac::FType, 3> (::frac::CommandHandler::random_vector)(const std::array<::frac::FType, 6>& values)
{
  std::array<::frac::FType, 3> result{};
  for (int i = 0; i < 3; ++i) {
    result[i] = rndm.rand(values[2 * i], values[2 * i + 1]);
  }
  return result;
}

void frac::CommandHandler::handle(const ::frac::Terminal& term)
{
  switch (term.ttype) {
  case Terminal::TerminalType::ROTATE_TERM:
    fractal.rotate(random_vector(term.values));
    break;
  case Terminal::TerminalType::MOVE_TERM:
    fractal.move(random_number(term.values));
    break;
  case Terminal::TerminalType::DRAW_TERM:
    fractal.draw(random_number(term.values));
    break;
  case Terminal::TerminalType::FACE_TERM:
    fractal.face(random_number(term.values));
    break;
  case Terminal::TerminalType::ENDFACE_TERM:
    fractal.endface();
    break;
  case Terminal::TerminalType::PUSH_TERM:
    fractal.push();
    break;
  case Terminal::TerminalType::POP_TERM:
    fractal.pop();
    break;
  case Terminal::TerminalType::EMPTY:
    throw std::runtime_error("Iterated to empty terminal");
  default:
    throw std::runtime_error("Unknown terminal");
  }
}
