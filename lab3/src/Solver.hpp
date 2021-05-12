#pragma once
#include "include.hpp"

class Solver {
  Context *ContextPtr;

public:
  Solver(Context *ContextPtr) : ContextPtr(ContextPtr) {}
  double solve() {
    ContextPtr->buildBDD();
    if (ContextPtr->isTrue())
      return 1;
    if (ContextPtr->isFalse())
      return 0;
    char FileName[] = "out.dot";
    ContextPtr->writeDot(FileName);
    Parser P;
    auto PG = P.dotParse(FileName);
    std::vector<std::vector<std::pair<int, double>>> Edge(P.NameMap.size());
    for (auto E : PG) {
      int A, B;
      bool Pos;
      std::tie(A, B, Pos) = E;
      double Prob = ContextPtr->getProb(P.LevelMap[A], Pos);
      Edge[A].emplace_back(B, Prob);
    }
    std::vector<double> DP(P.NameMap.size(), -1);
    DP.back() = 1;
    DP[DP.size() - 2] = 0;
    dfs(0, Edge, DP);
    return DP[0];
  }
  void dfs(int Nd, std::vector<std::vector<std::pair<int, double>>> &Edge,
           std::vector<double> &DP) {
    if (DP[Nd] > -0.5)
      return;
    DP[Nd] = 0;
    for (auto E : Edge[Nd]) {
      int Chd = E.first;
      double Prob = E.second;
      dfs(Chd, Edge, DP);
      DP[Nd] += DP[Chd] * Prob;
    }
  }
};