#pragma once
#include "Context.hpp"
#include "Parser.hpp"
#include <iostream>

class Solver {
  Context *ContextPtr;

public:
  Solver(Context *ContextPtr) : ContextPtr(ContextPtr) {}
  double solve() {
    std::cerr << "Build\n";
    ContextPtr->buildBDD();
    std::cerr << "Output\n";
    char FileName[] = "out.dot";
    ContextPtr->writeDot(FileName);
    // TODO
    Parser P;
    auto E = P.dotParse(FileName);
    return 0.0; // TODO
  }
};