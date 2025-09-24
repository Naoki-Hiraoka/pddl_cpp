#ifndef PDDL_CPP_EFFECT_H
#define PDDL_CPP_EFFECT_H

#include <vector>
#include <memory>
#include <pddl_cpp/common.h>

namespace pddl_cpp {

  class Effect {
  };

  class EffectAnd: public Effect{
    std::vector<std::shared_ptr<Effect> > values;
  };
  class EffectLiteral: public Effect{
    AtomicFormula value;
  };
  class EffectForall: public Effect{
    std::vector<std::shared_ptr<Effect> > values;
  };
  class EffectWhen: public Effect{
    std::shared_ptr<GoalDescription> condition;
    std::shared_ptr<Effect> values;
  };
};

#endif
