#include "literal.h"

#include <stdexcept>

#include "lgrammarVisitor.h"

void NonTerminal::iterator::findTerminal() {
  while (not iterator_stack.empty() and
         (iterator_stack.top().first >= iterator_stack.top().second.size() or
          not iterator_stack.top().second.isTerminal(
              iterator_stack.top().first))) {
    std::cout << "At Stack #" << iterator_stack.size() << " Index #" << iterator_stack.top().first << "/" << iterator_stack.top().second.size() << std::endl;
    if (iterator_stack.top().first >= iterator_stack.top().second.size()) {
        std::cout << "popping stack #" << iterator_stack.size() << std::endl;
      iterator_stack.pop();
      if (iterator_stack.empty())
        return;
      ++iterator_stack.top().first;
    } else {
      if (getCurrentLevel() < wanted_level) {
      std::cout << "appending nt trans " << iterator_stack.top()
                        .second.list_NT[iterator_stack.top().first]
                        ->name << std::endl;
        push_holder(iterator_stack.top()
                        .second.list_NT[iterator_stack.top().first]
                        ->trans);
      } else if (getCurrentLevel() == wanted_level) {
      std::cout << "appending nt final trans " << iterator_stack.top()
                        .second.list_NT[iterator_stack.top().first]
                        ->name << std::endl;
        push_holder(iterator_stack.top()
                        .second.list_NT[iterator_stack.top().first]
                        ->final_trans);
      } else {
        throw std::runtime_error("Iterated deeper than desired level");
      }
    }
  }
}

NonTerminal::iterator &NonTerminal::iterator::operator++() {
  if (iterator_stack.empty())
    return *this;

  ++(iterator_stack.top().first);
  findTerminal();
  return *this;
}

const Terminal *NonTerminal::iterator::operator*() const {
  return &(iterator_stack.top().second.list_T[iterator_stack.top().first]);
}

void NonTerminal::iterator::decreaseCurrentLevel() {
    iterator_stack.pop();
}
