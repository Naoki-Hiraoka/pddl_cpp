#include <pddl_cpp/pddl_cpp.h>
#include <ros/ros.h>

namespace pddl_cpp {

  Object::Object() {}
  Object::Object(const std::string& name_) : name(name_) {}
  Object::Object(const std::string& name_, const std::string& type_) : name(name_), type(type_) {}


  bool Planner::plan(const Domain& domain,
                     const Problem& problem,
                     double max_planning_time,
                     std::vector<Step>& sequence,
                     std::string& data,
                     bool use_durative_action) {

    if(!ros::isInitialized()){
      ros::init(ros::M_string(), "pddl_client");
    }

    if(!this->ac_){
      this->ac_ = std::make_shared<actionlib::SimpleActionClient<pddl_msgs::PDDLPlannerAction> >("pddl_planner",true); // true causes the client to spin its own thread
    }

    this->ac_->waitForServer();

    pddl_msgs::PDDLPlannerGoal goal;
    goal.domain.name = domain.name;
    goal.domain.requirements = domain.requirements;
    goal.domain.types.resize(domain.types.size());
    for(int i=0;i<domain.types.size();i++){
      goal.domain.types[i] = domain.types[i];
    }
    goal.domain.constants.resize(domain.constants.size());
    for(int i=0;i<domain.constants.size();i++){
      goal.domain.constants[i] = domain.constants[i];
    }
    goal.domain.predicates.resize(domain.predicates.size());
    for(int i=0;i<domain.predicates.size();i++){
      goal.domain.predicates[i] = domain.predicates[i];
    }
    goal.domain.actions.resize(domain.actions.size());
    for(int i=0;i<domain.actions.size();i++){
      goal.domain.actions[i].name = domain.actions[i].name;
      goal.domain.actions[i].parameters = domain.actions[i].parameters;
      goal.domain.actions[i].precondition = domain.actions[i].precondition;
      goal.domain.actions[i].effect = domain.actions[i].effect;
      goal.domain.actions[i].on_condition = domain.actions[i].on_condition;
      goal.domain.actions[i].action_duration = domain.actions[i].action_duration;
    }
    goal.domain.functions.resize(domain.functions.size());
    for(int i=0;i<domain.functions.size();i++){
      goal.domain.functions[i] = domain.functions[i];
    }
    goal.problem.name = problem.name;
    goal.problem.domain = problem.domain;
    goal.problem.objects.resize(problem.objects.size());
    for(int i=0;i<problem.objects.size();i++){
      goal.problem.objects[i].name = problem.objects[i].name;
      goal.problem.objects[i].type = problem.objects[i].type;
    }
    goal.problem.initial.resize(problem.initial.size());
    for(int i=0;i<problem.initial.size();i++){
      goal.problem.initial[i] = problem.initial[i];
    }
    goal.problem.goal = problem.goal;
    goal.problem.metric = problem.metric;
    goal.max_planning_time = ros::Duration(max_planning_time);

    actionlib::SimpleClientGoalState state = ac_->sendGoalAndWait(goal, ros::Duration(max_planning_time + 3.0));

    if(state != actionlib::SimpleClientGoalState::SUCCEEDED){
      return false;
    }

    pddl_msgs::PDDLPlannerResultConstPtr result = ac_->getResult();
    sequence.resize(result->sequence.size());
    for(int i=0;i<result->sequence.size();i++){
      sequence[i].action = result->sequence[i].action;
      sequence[i].args.resize(result->sequence[i].args.size());
      for(int j=0;j<result->sequence[i].args.size();j++){
        sequence[i].args[j] = result->sequence[i].args[j];
      }
      sequence[i].start_time = result->sequence[i].start_time;
      sequence[i].action_duration = result->sequence[i].action_duration;
    }
    data.clear();
    data.reserve(result->data.size());
    for(int i=0;i<result->data.size();i++){
      data += result->data[i];
    }
    use_durative_action = result->use_durative_action;

    return true;
  }

};
