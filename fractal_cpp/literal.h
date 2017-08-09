#include <functional>
#include <stack>
#include <utility>
#include <vector>

class Terminal {
public:
  enum TerminalType { RTERM, MTERM, DTERM, PUTERM, POTERM };

private:
  TerminalType ttype;
};

class NonTerminal;
class Define;
struct NTHolder {
  std::vector<NonTerminal *> list_NT;
  std::vector<Define *> list_DEF;
  std::vector<Terminal> list_T;

  bool isTerminal(std::size_t index) const {
    return not (list_NT[index] or list_DEF[index]);
  }

  bool isDefine(std::size_t index) const { return not list_DEF[index]; }

  std::size_t size() const { return list_NT.size(); }
};

class Define {
public:
  NTHolder trans;
};

class NonTerminal {
public:
  NTHolder trans;
  NTHolder final_trans;
  class iterator;
  iterator iterate(unsigned int level);

  class iterator : public std::iterator<std::output_iterator_tag, Terminal *> {
  private:
    unsigned int wanted_level;
    std::stack<std::pair<unsigned int, const NTHolder &>> iterator_stack;
    std::stack<unsigned int> define_stack;

    void findTerminal();
    void push_holder(const NTHolder &trans) {
      iterator_stack.push(std::make_pair(0, trans));
    }
    unsigned int getCurrentLevel() {
      return iterator_stack.size() - define_stack.size();
    }
    void decreaseCurrentLevel();

  public:
    explicit iterator(const NTHolder &trans, unsigned int depth) {
      iterator_stack.push(std::make_pair(0, std::cref(trans)));
      wanted_level = depth;
    };
    const Terminal *operator*() const;
    iterator &operator++();
  };
};
