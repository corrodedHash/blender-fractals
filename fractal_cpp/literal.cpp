#include "literal.h"
#include <cassert>

void NonTerminal::iterator::findTerminal() {
  while (not iterator_stack.empty() and
         (iterator_stack.top().first >= iterator_stack.top().second.size() or
          not iterator_stack.top().second.isTerminal(
              iterator_stack.top().first))) {
    if (iterator_stack.top().first >= iterator_stack.top().second.size()) {
      iterator_stack.pop();
      if (iterator_stack.empty())
        return;
      ++iterator_stack.top().first;
    } else {
      if (iterator_stack.top().second.isDefine(iterator_stack.top().first)) {
        push_holder(iterator_stack.top()
                        .second.list_DEF[iterator_stack.top().first]
                        ->trans);
        define_stack.push(iterator_stack.size());
      } else {
        if (getCurrentLevel() < wanted_level) {
          push_holder(iterator_stack.top()
                          .second.list_NT[iterator_stack.top().first]
                          ->trans);
        } else if (getCurrentLevel() == wanted_level) {
          push_holder(iterator_stack.top()
                          .second.list_NT[iterator_stack.top().first]
                          ->final_trans);
        } else {
          assert(false);
        }
      }
    }
  }
}

NonTerminal::iterator &NonTerminal::iterator::operator++() {
  if (iterator_stack.empty())
    return *this;

  ++iterator_stack.top().first;
  findTerminal();
  return *this;
}

const Terminal *NonTerminal::iterator::operator*() const {
  return &(iterator_stack.top().second.list_T[iterator_stack.top().first]);
}

void NonTerminal::iterator::decreaseCurrentLevel() {
  if (not define_stack.empty() and
      define_stack.top() == iterator_stack.size()) {
    define_stack.pop();
    iterator_stack.pop();
  } else {
    iterator_stack.pop();
  }
}
