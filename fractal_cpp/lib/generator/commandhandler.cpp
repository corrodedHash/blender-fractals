#include "generator/commandhandler.h"
#include <cstdlib>

double CommandHandler::rand(double start, double end)
{
  if (start == end)
    return start;
  return ((std::rand() / static_cast<double>(RAND_MAX)) * (start - end)) + start;
}

double CommandHandler::random_double(const std::array<double, 6>& values)
{
  return rand(values[0], values[1]);
}

std::array<double, 3> CommandHandler::random_vector(const std::array<double, 6>& values)
{
  std::array<double, 3> result;
  for (int i = 0; i < 3; ++i) {
    result[i] = rand(values[2 * i], values[2 * i + 1]);
  }
  return result;
}

void CommandHandler::handle(const Terminal& term)
{
  switch (term.ttype) {
  case Terminal::ROTATE_TERM:
    fractal.rotate(random_vector(term.values));
    break;
  case Terminal::MOVE_TERM:
    fractal.move(random_double(term.values));
    break;
  case Terminal::DRAW_TERM:
    fractal.draw(random_double(term.values));
    break;
  case Terminal::FACE_TERM:
    fractal.face(random_double(term.values));
    break;
  case Terminal::ENDFACE_TERM:
    fractal.endface();
    break;
  case Terminal::PUSH_TERM:
    fractal.push();
    break;
  case Terminal::POP_TERM:
    fractal.pop();
    break;
  case Terminal::EMPTY:
    throw std::runtime_error("Iterated to empty terminal");
  default:
    throw std::runtime_error("Unknown terminal");
  }
}
