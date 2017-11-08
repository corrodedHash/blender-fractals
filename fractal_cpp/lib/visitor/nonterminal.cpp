#include "visitor/nonterminal.h"

#include <cassert>
#include <stdexcept>
#include <iostream>

NonTerminalTree NonTerminal::get_tree(unsigned int depth)
{
  return NonTerminalTree(*this, depth);
}

void NonTerminalTree::iterator::findTerminal()
{
  while (not iterator_stack.empty() and (iterator_stack.top().finished() or not iterator_stack.top().cur_is_term())) {
    if (iterator_stack.top().finished()) {
      iterator_stack.pop();
      if (iterator_stack.empty())
        return;
      ++iterator_stack.top().index;
    } else {
      assert(not iterator_stack.top().cur_is_term());
      if (getCurrentLevel() < wanted_level) {
        push_holder(iterator_stack.top().get_cur_nt()->trans);
      } else if (getCurrentLevel() == wanted_level) {
        push_holder(iterator_stack.top().get_cur_nt()->final_trans);
      } else {
        throw std::runtime_error("Iterated deeper than desired level");
      }
    }
  }
}

NonTerminalTree::iterator& NonTerminalTree::iterator::operator++()
{
  if (iterator_stack.empty())
    return *this;

  ++(iterator_stack.top().index);
  findTerminal();
  return *this;
}

const Terminal& NonTerminalTree::iterator::operator*() const
{
  assert(not iterator_stack.empty());
  return iterator_stack.top().get_cur_term();
}

void NonTerminalTree::iterator::decreaseCurrentLevel()
{
  iterator_stack.pop();
}

NonTerminalTree::iterator NonTerminalTree::begin()
{
  if (depth == 0) {
    return iterator(nt.final_trans, 0);
  } else {
    return iterator(nt.trans, depth);
  }
}

NonTerminalTree::iterator NonTerminalTree::end()
{
  return iterator(depth);
}
