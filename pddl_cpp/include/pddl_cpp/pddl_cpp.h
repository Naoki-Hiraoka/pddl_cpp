#ifndef PDDL_CPP_PDDL_CPP_H
#define PDDL_CPP_PDDL_CPP_H

#include <string>
#include <vector>
#include <memory>
#include <actionlib/client/simple_action_client.h>
#include <pddl_msgs/PDDLPlannerAction.h>

namespace pddl_cpp {

  class Action {
  public:
    std::string name;
    std::string parameters;
    std::string precondition;
    std::string effect;
    std::string on_condition;
    std::string action_duration;
  };

  class Domain {
  public:
    std::string name;
    std::string requirements;
    std::vector<std::string> types;
    std::vector<std::string> constants;
    std::vector<std::string> predicates;
    std::vector<Action> actions;
    std::vector<std::string> functions;
  };

  class Object {
  public:
    std::string name;
    std::string type;
  };

  class Problem {
  public:
    std::string name;
    std::string domain;
    std::vector<Object> objects;
    std::vector<std::string> initial;
    std::string goal;
    std::string metric;
  };

  class Step {
  public:
    std::string action;
    std::vector<std::string> args;
    std::string start_time;
    std::string action_duration;
  };

  class Planner {
  public:
    bool plan(const Domain& domain,
              const Problem& problem,
              double max_planning_time,
              std::vector<Step>& sequence,
              std::vector<std::string>& data,
              bool use_durative_action);

    std::string actionName;
  protected:
    std::shared_ptr<actionlib::SimpleActionClient<pddl_msgs::PDDLPlannerAction> > ac_;
  };
};

#endif
