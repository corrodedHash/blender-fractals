#include "generator/fractalgen.h"
#include "generator/commandhandler.h"
#include "visitor/lgrammarVisitor.h"

#include "lsystemLexer.h"
#include "lsystemParser.h"

#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"

#include <fstream>

#include <iostream>

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
