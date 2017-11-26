#include "generator/fractalgen.h"
#include "generator/commandhandler.h"
#include "visitor/lgrammarVisitor.h"

#include "lsystemLexer.h"
#include "lsystemParser.h"

#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"

#include <fstream>

#include <iostream>
#include <stdexcept>


class mylexer: public antlr::lsystemLexer {
  virtual void recover(antlr4::RecognitionException *re) override{
    throw antlr4::ParseCancellationException();
  }
  virtual void recover(const antlr4::LexerNoViableAltException &e) override{
    throw antlr4::ParseCancellationException();
  }
  public:
  mylexer(antlr4::CharStream *input): antlr::lsystemLexer(input){}
};

static frac::NonTerminalManager parseGrammar(antlr4::ANTLRInputStream istream){
  mylexer my_lexer(&istream);
  my_lexer.removeErrorListeners();
  antlr4::CommonTokenStream my_tokenstream(&my_lexer);
  antlr::lsystemParser my_parser(&my_tokenstream);
  my_parser.setErrorHandler(std::make_shared<antlr4::BailErrorStrategy>());
  my_parser.removeErrorListeners();
  antlr::lgrammarVisitor my_visitor;
  return my_visitor.visit(my_parser.code());
}

static frac::NonTerminalManager parseGrammar(const std::string& filename)
{
  std::ifstream grammarfile;
  grammarfile.open(filename);
  return parseGrammar(antlr4::ANTLRInputStream(grammarfile));
}

static frac::NonTerminalManager parseStringGrammar(const char data[], size_t size)
{
  return parseGrammar(antlr4::ANTLRInputStream (data, size));
}

static frac::FractalGen generateFractal(::frac::NonTerminalManager ntm, unsigned int level){
  if (ntm.start == nullptr){
    throw std::runtime_error("Did not parse grammar");
  }
  ::frac::FractalGen myFrac;
  ::frac::CommandHandler comhandler(myFrac);
  auto nt_tree = ntm.start->get_tree(level);
  for (auto term: nt_tree) {
    comhandler.handle(term);
  }
  return myFrac;
}


::frac::FractalGen frac::generateFractal(const std::string& filename,
    unsigned int level)
{
  return ::generateFractal(parseGrammar(filename), level);
}


::frac::FractalGen frac::generateFractal(const char data[], size_t size,
    unsigned int level)
{
  return ::generateFractal(parseStringGrammar(data, size), level);
}

::frac::MeshInfo frac::generateMesh(const std::string& filename,
    unsigned int level)
{
  return MeshInfo(generateFractal(filename, level).output());
}
