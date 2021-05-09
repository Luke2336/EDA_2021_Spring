#pragma once
#include "Context.hpp"
#include "cudd.h"
#include "util.h"
#include <string>
#include <vector>

struct Variable {
  int id;
  bool sign; // true : pos / false : neg

  Variable() {}
  Variable(int id, bool sign) : id(id), sign(sign) {}
};

class Context {
  double Prob[26];
  const std::vector<std::vector<Variable>> Equations;
  DdNode *BDD;
  std::vector<int> Vars;
  DdManager *GBM;

public:
  Context(const double arr[26], const std::vector<std::vector<Variable>> &input,
          const std::vector<int> &Vars)
      : Equations(input), Vars(Vars),
        GBM(Cudd_Init(26, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0)) {
    for (int i = 0; i < 26; ++i) {
      Prob[i] = arr[i];
    }
  }
  void buildBDD() {
    DdNode *Tmp;
    BDD = Cudd_ReadLogicZero(GBM);
    Cudd_Ref(BDD);
    for (const auto Equation : Equations) {
      DdNode *Term = Cudd_ReadOne(GBM);
      for (const auto Var : Equation) {
        DdNode *Node = Var.sign ? Cudd_bddIthVar(GBM, Var.id)
                                : Cudd_Not(Cudd_bddIthVar(GBM, Var.id));
        Tmp = Cudd_bddAnd(GBM, Node, Term);
        Cudd_Ref(Tmp);
        Cudd_RecursiveDeref(GBM, Term);
        Term = Tmp;
      }
      Tmp = Cudd_bddOr(GBM, Term, BDD);
      Cudd_Ref(Tmp);
      Cudd_RecursiveDeref(GBM, BDD);
      BDD = Tmp;
    }
  }
  void writeDot(char *FileName) {
    Cudd_BddToAdd(GBM, BDD);
    FILE *File;
    File = fopen(FileName, "w");
    DdNode **DdNodeArr = (DdNode **)malloc(sizeof(DdNode *));
    DdNodeArr[0] = BDD;
    Cudd_DumpDot(GBM, 1, DdNodeArr, NULL, NULL, File);
    free(DdNodeArr);
    fclose(File);
    Cudd_Quit(GBM);
  }
  double getProb(int i, bool b) const { return b ? Prob[i] : 1 - Prob[i]; }
  const std::vector<std::vector<Variable>> &getEquations() const {
    return Equations;
  }
};