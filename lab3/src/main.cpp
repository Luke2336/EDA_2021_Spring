#include "include.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3)
    assert(false && "Argument error!!");
  freopen(argv[1], "r", stdin);
  freopen(argv[2], "w", stdout);
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  Parser P;
  std::vector<std::vector<Variable>> Equation;
  double Prob[26];
  std::vector<int> Vars;
  P.parser(Prob, Equation, Vars);
  Context SolverContext(Prob, Equation, Vars);
  Solver MySolver(&SolverContext);
  std::cout << std::fixed << std::setprecision(3) << MySolver.solve() << '\n';
  return 0;
}