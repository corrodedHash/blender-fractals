#include "generator/fractalgen.h"
#include "visitor/lgrammarVisitor.h"

#include "lsystemLexer.h"
#include "lsystemParser.h"

#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"

#include <fstream>

#include <cmath>

#include <iostream>

static NonTerminalManager parseGrammar(const std::string &filename) {
  std::ifstream grammarfile;
  grammarfile.open(filename);
  antlr4::ANTLRInputStream my_input(grammarfile);
  antlr::lsystemLexer my_lexer(&my_input);
  antlr4::CommonTokenStream my_tokenstream(&my_lexer);
  antlr::lsystemParser my_parser(&my_tokenstream);
  antlr::lgrammarVisitor my_visitor;
  return my_visitor.visit(my_parser.code());
}

static void handle_command(const Terminal *term, FractalGen<double>& fractal) {
  switch (term->ttype) {
  case Terminal::ROTATE_TERM:
    fractal.rotate(term->values);
    break;
  case Terminal::MOVE_TERM:
    fractal.move(term->values[0]);
    break;
  case Terminal::DRAW_TERM:
    fractal.draw(term->values[0]);
    break;
  case Terminal::FACE_TERM:
    fractal.face(term->values[0]);
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

mesh_info<double> generateMesh(const std::string &filename,
                                      unsigned int level) {
  NonTerminalManager ntm = parseGrammar(filename);
  FractalGen<double> myFrac;
  for (NonTerminal::iterator it = ntm.start->iterate(level); not it.end();
       ++it) {
    handle_command(*it, myFrac);
  }
  mesh_info<double> result(myFrac.output());
  return result;
}
