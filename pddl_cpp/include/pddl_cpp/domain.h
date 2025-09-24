#ifndef PDDL_CPP_DOMAIN_H
#define PDDL_CPP_DOMAIN_H

#include <vector>
#include <pddl_cpp/common.h>
#include <pddl_cpp/action.h>
namespace pddl_cpp {

  class Domain {
  public:
    std::vector<std::string> requirements; // ":typing"など
    std::vector<Type> types;
    std::vector<Type> constants;
    std::vector<AtomicFormulaSkeleton> predicates;
    std::vector<Action> actions;
    // axioms
  };
};

#endif
