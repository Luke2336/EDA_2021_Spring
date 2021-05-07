#include "Context.hpp"
#include "Parser.hpp"
#include <cassert>
#include <string>
#include <vector>
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
  P.parser(Prob, Equation);
  Context SolverContext(Prob, Equation);
  return 0;
}