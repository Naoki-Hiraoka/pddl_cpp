#ifndef PDDL_CPP_COMMON_H
#define PDDL_CPP_COMMON_H

#include <vector>
#include <string>

namespace pddl_cpp {

  // std::vector<Type> でtyped_listを表す.
  class Type {
  public:
    std::string name;
    std::string parent = "object";
  };

  class AtomicFormulaSkeleton {
  public:
    std::string name;
    std::vector<Type> variables;
  };

  class AtomicFormula {
  public:
    std::string predicate;
    std::vector<std::string> arguments;
  };

  class Literal {
  public:
    bool tf = true;
    AtomicFormula atomicFormula;
  };
};

#endif
