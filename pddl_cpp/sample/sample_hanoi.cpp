#include <pddl_cpp/pddl_cpp.h>
#include <iostream>

int main (){
  pddl_cpp::Domain domain;
  domain.name = "hanoi";
  domain.requirements = ":typing";
  domain.types.emplace_back("object");
  domain.predicates.emplace_back("(on ?obj0 ?obj1 - object)");
  domain.predicates.emplace_back("(clear ?obj - object)");
  domain.predicates.emplace_back("(can-be-on ?obj0 ?obj1 - object)");
  {
    pddl_cpp::Action action;
    action.name = "move";
    action.parameters = "(?obj ?from ?to - object)";
    action.precondition = "(and (clear ?obj) (clear ?to) (on ?obj ?from) (can-be-on ?obj ?to))";
    action.effect = "(and (on ?obj ?to) (not (on ?obj ?from)) (not (clear ?to)) (clear ?from))";
    domain.actions.push_back(action);
  }

  pddl_cpp::Problem problem;
  problem.name = "hanoi0";
  problem.domain = "hanoi";
  problem.objects.emplace_back("disk0", "object");
  problem.objects.emplace_back("disk1", "object");
  problem.objects.emplace_back("disk2", "object");
  problem.objects.emplace_back("pole0", "object");
  problem.objects.emplace_back("pole1", "object");
  problem.objects.emplace_back("pole2", "object");
  problem.initial.emplace_back("(on disk0 disk1)");
  problem.initial.emplace_back("(on disk1 disk2)");
  problem.initial.emplace_back("(on disk2 pole0)");
  problem.initial.emplace_back("(can-be-on disk0 disk1)");
  problem.initial.emplace_back("(can-be-on disk1 disk2)");
  problem.initial.emplace_back("(clear pole1)");
  problem.initial.emplace_back("(clear pole2)");
  problem.initial.emplace_back("(clear disk0)");
  for(int i=0;i<=2;i++){
    for(int j=0;j<=2;j++){
      problem.initial.emplace_back("(can-be-on disk" + std::to_string(i) + " pole" + std::to_string(j) + ")");
    }
  }
  problem.goal = "(and (on disk0 disk1) (on disk1 disk2) (on disk2 pole2) (clear pole0) (clear pole1) (clear disk0))";

  pddl_cpp::Planner planner;
  std::vector<pddl_cpp::Step> sequence;
  std::string data;
  bool result = planner.plan(domain,
                             problem,
                             30.0,
                             sequence,
                             data,
                             false);
  std::cout << data << std::endl;
  if(result){
    std::cout << "solved" << std::endl;
    for(int i=0;i<sequence.size();i++){
      std::cout << i << ": " << sequence[i].action;
      for(int j=0;j<sequence[i].args.size();j++){
        std::cout << " " << sequence[i].args[j];
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
