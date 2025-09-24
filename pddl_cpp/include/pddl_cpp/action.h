#ifndef PDDL_CPP_ACTION_H
#define PDDL_CPP_ACTION_H

#include <vector>
#include <memory>
#include <pddl_cpp/common.h>
#include <pddl_cpp/goal_description.h>
#include <pddl_cpp/effect.h>

namespace pddl_cpp {

  class Action {
  public:
    std::string name;
    std::vector<Type> parameters;
    std::shared_ptr<GoalDescription> precondition;
    std::shared_ptr<Effect> effect;
  };
};

#endif
