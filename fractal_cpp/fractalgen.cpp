#include "fractalgen.h"
#include "lgrammarVisitor.h"

#include "parsing/lsystemLexer.h"
#include "parsing/lsystemParser.h"

#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"

#include <cmath>
#include <fstream>

const double rad_degree_constant = (4. * std::atan(1.)) / 180.;

template <typename U>
std::valarray<U> FractalGen<U>::axis_rotate(const std::valarray<U> &input,
                                            const std::valarray<U> &axis,
                                            U degree) {
  return input * (input * axis) +
         std::cos(degree * rad_degree_constant) *
             cross(cross(input, axis), input) +
         std::sin(degree * rad_degree_constant) * cross(input, axis);
}

template <typename U> void FractalGen<U>::move(U distance) {
  moved = true;
  position_stack.top() = rotation_stack.top() * distance;
}

template <typename U> void FractalGen<U>::draw(U distance) {
  if (moved) {
    moved = false;
    verts.insert(std::begin(verts), std::begin(position_stack.top()),
                 std::end(position_stack.top()));
    verts_stack.top() = verts.size() / 3;
  }
  position_stack.top() += (rotation_stack.top() * distance);

  verts.insert(std::begin(verts), std::begin(position_stack.top()),
               std::end(position_stack.top()));
  edges.push_back(verts_stack.top());
  edges.push_back(verts.size() / 3);
}

template <typename U> void FractalGen<U>::face(U distance) {}

template <typename U>
void FractalGen<U>::rotate(const std::array<U, 3> &rotation) {
  rotation_stack.top() =
      axis_rotate(rotation_stack.top(), look_at_stack.top(), rotation[0]);
  if (rotation[1] != 0) {
    std::valarray<U> rot_axis =
        cross(rotation_stack.top(), look_at_stack.top());
    rotation_stack.top() =
        axis_rotate(rotation_stack.top(), rot_axis, rotation[1]);
    look_at_stack.top() =
        axis_rotate(look_at_stack.top(), rot_axis, rotation[1]);
  }
}

template <typename U> void FractalGen<U>::push() {
  position_stack.push(position_stack.top());
  rotation_stack.push(rotation_stack.top());
  look_at_stack.push(look_at_stack.top());
  verts_stack.push(verts_stack.top());
}
template <typename U> void FractalGen<U>::pop() {
  position_stack.pop();
  rotation_stack.pop();
  look_at_stack.pop();
  verts_stack.pop();
}
template <typename U> void FractalGen<U>::endface() {}

template <typename U> void FractalGen<U>::handle_command(const Terminal *term) {
  std::cout << "Command: " << term->ttype << std::endl;
  switch (term->ttype) {
  case Terminal::ROTATE_TERM:
    this->rotate(term->values);
    break;
  case Terminal::MOVE_TERM:
    this->move(term->values[0]);
    break;
  case Terminal::DRAW_TERM:
    this->draw(term->values[0]);
    break;
  case Terminal::FACE_TERM:
    this->face(term->values[0]);
    break;
  case Terminal::ENDFACE_TERM:
    this->endface();
    break;
  case Terminal::PUSH_TERM:
    this->push();
    break;
  case Terminal::POP_TERM:
    this->pop();
    break;
  case Terminal::EMPTY:
    throw std::runtime_error("Iterated to empty terminal");
  default:
    throw std::runtime_error("Unknown terminal");
  }
}

template <typename U>
mesh_info<U> FractalGen<U>::output(){
  mesh_info<U> result;
  result.vert_size = verts.size();
  result.edge_size = edges.size();
  result.face_size = faces.size();
  result.verts = new U[verts.size()];
  result.edges = new std::size_t[edges.size()];
  result.faces = new std::size_t[faces.size()];
  std::copy(std::begin(verts), std::end(verts), result.verts);
  std::copy(std::begin(edges), std::end(edges), result.edges);
  std::copy(std::begin(faces), std::end(faces), result.faces);
  return result;
}

inline NonTerminalManager parseGrammar(const std::string &filename) {
  std::ifstream grammarfile;
  grammarfile.open(filename);
  antlr4::ANTLRInputStream my_input(grammarfile);
  lsystemLexer my_lexer(&my_input);
  antlr4::CommonTokenStream my_tokenstream(&my_lexer);
  lsystemParser my_parser(&my_tokenstream);
  lgrammarVisitor my_visitor;
  return my_visitor.visit(my_parser.code());
}

mesh_info<double> generateMesh(const std::string &filename,
                               unsigned int level) {
  NonTerminalManager ntm = parseGrammar(filename);
  FractalGen<double> myFrac;
  for (NonTerminal::iterator it = ntm.start->iterate(level); not it.end();
       ++it) {
    myFrac.handle_command(*it);
  }
  return myFrac.output();
}