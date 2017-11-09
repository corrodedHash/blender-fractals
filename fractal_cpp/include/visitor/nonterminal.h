#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "visitor/ntholder.h"

class NonTerminal;
class NonTerminalTree {
  public:
  class iterator;

  NonTerminal& nt;
  unsigned int depth;

  NonTerminalTree(NonTerminal& nt_, unsigned int depth_)
      : nt(nt_)
      , depth(depth_)
  {
  }
  iterator begin();
  iterator end();
};

class NonTerminal {
  public:
  std::string name;
  NTHolder trans;
  NTHolder final_trans;
  NonTerminal(const std::string& _name)
      : name(_name){};
  NonTerminal(std::string&& _name)
      : name(_name){};

  // TODO: Should make a map to allow multiple transitions
  void addTrans(NTHolder _trans) { trans = _trans; }
  void addFinalTrans(NTHolder _final_trans) { final_trans = _final_trans; }

  NonTerminalTree get_tree(unsigned int depth);
};

struct FlatNonterminal {
  const NTHolder& nt;
  unsigned int index;
  FlatNonterminal(const NTHolder& nt_)
      : nt(nt_)
      , index(0)
  {
  }
  bool finished() const
  {
    return index >= nt.size();
  }
  bool cur_is_term() const{
    return nt.isTerminal(index);
  }
  const NonTerminal* get_cur_nt() const{
    assert(not cur_is_term());
    return nt.list_NT[index];
  }
  const Terminal& get_cur_term() const{
    assert(cur_is_term());
    return nt.list_T[index];
  }

  bool operator==(const FlatNonterminal& other) const
  {
    return index == other.index and nt == other.nt;
  }
  bool operator!=(const FlatNonterminal& other) const
  {
    return not(*this == other);
  }
};

class NonTerminalTree::iterator : public std::iterator<std::output_iterator_tag, Terminal> {
  private:
  unsigned int wanted_level;
  std::stack<FlatNonterminal> iterator_stack;

  void findTerminal();
  void push_holder(const NTHolder& trans)
  {
    iterator_stack.push(FlatNonterminal(trans));
  }
  unsigned int getCurrentLevel() { return iterator_stack.size(); }
  void decreaseCurrentLevel();

  public:
  explicit iterator(const NTHolder& trans, unsigned int depth)
  {
    push_holder(trans);
    wanted_level = depth;
    if (not iterator_stack.top().cur_is_term())
      findTerminal();
  };
  explicit iterator(unsigned int depth)
  {
    wanted_level = depth;
  };
  const Terminal& operator*() const;
  iterator& operator++();
  bool operator==(const iterator& other) const
  {
    return wanted_level == other.wanted_level and iterator_stack == other.iterator_stack;
  }
  bool operator!=(const iterator& other) const
  {
    return not(*this == other);
  }
};
