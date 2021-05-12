#pragma once
#include "Context.hpp"
#include "cudd.h"
#include "util.h"
#include <cstdio>
#include <iostream>
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
          const std::vector<int> &Vars, int Reorder = 0)
      : Equations(input), Vars(Vars), GBM(initGBM(Reorder)) {
    for (int i = 0; i < 26; ++i) {
      Prob[i] = arr[i];
    }
  }

  DdManager *initGBM(int Reorder) {
    DdManager *gbm = Cudd_Init(26, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);
    switch (Reorder) {
    case 1:
      // Dynamic reordering by sifting
      Cudd_AutodynEnable(gbm, CUDD_REORDER_SYMM_SIFT);
      Cudd_ReduceHeap(gbm, CUDD_REORDER_SYMM_SIFT, 3000);
      break;
    case 2:
      // Dynamic reordering by window permutation
      Cudd_AutodynEnable(gbm, CUDD_REORDER_WINDOW2);
      Cudd_ReduceHeap(gbm, CUDD_REORDER_WINDOW2, 3000);
      break;
    case 3:
      // Dynamic reordering by simulated annealing
      Cudd_AutodynEnable(gbm, CUDD_REORDER_ANNEALING);
      Cudd_ReduceHeap(gbm, CUDD_REORDER_ANNEALING, 3000);
      break;
    case 4:
      // Dynamic reordering by genetic algorithm
      Cudd_AutodynEnable(gbm, CUDD_REORDER_GENETIC);
      Cudd_ReduceHeap(gbm, CUDD_REORDER_GENETIC, 3000);
      break;
    case 5:
      // Dynamic reordering by swapping
      Cudd_AutodynEnable(gbm, CUDD_REORDER_RANDOM);
      Cudd_ReduceHeap(gbm, CUDD_REORDER_RANDOM, 3000);
      break;
    default:
      // No reordering
      Cudd_AutodynDisable(gbm);
      break;
    }
    return gbm;
  }

  void print_dd(int n, int pr) {
    DdManager *gbm = GBM;
    DdNode *dd = BDD;
    printf("DdManager nodes: %ld | ", Cudd_ReadNodeCount(gbm));
    printf("DdManager vars: %d | ", Cudd_ReadSize(gbm));
    printf("DdManager reorderings: %d | ", Cudd_ReadReorderings(gbm));
    printf("DdManager memory: %ld \n", Cudd_ReadMemoryInUse(gbm));
    Cudd_PrintDebug(gbm, dd, n, pr);
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
    // print_dd(2, 4);
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