#include "generator/fractalgen.h"
#include "visitor/lgrammarVisitor.h"

#include "lsystemLexer.h"
#include "lsystemParser.h"

#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"

#include <fstream>

#include <cmath>
#include <cstdlib>


#include <iostream>
#include <random>

static NonTerminalManager parseGrammar(const std::string& filename)
{
  std::ifstream grammarfile;
  grammarfile.open(filename);
  antlr4::ANTLRInputStream my_input(grammarfile);
  antlr::lsystemLexer my_lexer(&my_input);
  antlr4::CommonTokenStream my_tokenstream(&my_lexer);
  antlr::lsystemParser my_parser(&my_tokenstream);
  antlr::lgrammarVisitor my_visitor;
  return my_visitor.visit(my_parser.code());
}

class CommandHandler {

  FractalGen<double>& fractal;
  std::random_device rd;
  std::mt19937 gen;

  public:
  CommandHandler(FractalGen<double>& fractal_)
      : fractal(fractal_), gen(rd()){};
  double rand(double start, double end){
    if (start == end)
      return start;
    return ((std::rand() / static_cast<double>(RAND_MAX)) * (start - end)) + start;
  }
  double random_double(const std::array<double, 6>& values)
  {
    //std::uniform_real_distribution<> dis(values[0], values[1]);
    //return dis(gen);
    return rand(values[0], values[1]);
  }

  std::array<double, 3> random_vector(const std::array<double, 6>& values)
  {
    std::array<double, 3> result;
    for (int i = 0; i < 3; ++i) {
      //std::uniform_real_distribution<> dis(values[2 * i], values[2 * i + 1]);
      //result[i] = dis(gen);
      result[i] = rand(values[2 * i], values[2 * i + 1]);
    }
    return result;
  }
  void handle(const Terminal& term)
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
};

mesh_info<double> generateMesh(const std::string& filename,
    unsigned int level)
{
  NonTerminalManager ntm = parseGrammar(filename);
  FractalGen<double> myFrac;
  CommandHandler comhandler(myFrac);
  auto nt_tree = ntm.start->get_tree(level);
  for (auto term: nt_tree) {
    comhandler.handle(term);
  }
  mesh_info<double> result(myFrac.output());
  return result;
}
