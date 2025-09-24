#ifndef PDDL_CPP_GOAL_DESCRIPTION_H
#define PDDL_CPP_GOAL_DESCRIPTION_H

#include <vector>
#include <memory>
#include <pddl_cpp/common.h>

namespace pddl_cpp {

  class GoalDescription {
  };

  class GoalDescriptionAtomicFormula: public GoalDescription{
    AtomicFormula value;
  };
  class GoalDescriptionAnd: public GoalDescription{
    std::vector<std::shared_ptr<GoalDescription> > values;
  };
  class GoalDescriptionLiteral: public GoalDescription{
    Literal value;
  };
  class GoalDescriptionOr: public GoalDescription{
    std::vector<std::shared_ptr<GoalDescription> > values;
  };
  class GoalDescriptionNot: public GoalDescription{
    std::shared_ptr<GoalDescription> value;
  };
  class GoalDescriptionExists: public GoalDescription{
    std::vector<Type> variables;
    std::shared_ptr<GoalDescription> value;
  };
  class GoalDescriptionForall: public GoalDescription{
    std::vector<Type> variables;
    std::shared_ptr<GoalDescription> value;
  };
};

#endif
