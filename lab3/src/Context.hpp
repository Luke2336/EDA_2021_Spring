#pragma once
#include "Context.hpp"
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

public:
  Context(const double arr[26], const std::vector<std::vector<Variable>> &input)
      : Equations(input) {
    for (int i = 0; i < 26; ++i)
      Prob[i] = arr[i];
  }
  double getProb(int i, bool b) const { return b ? Prob[i] : 1 - Prob[i]; }
  const std::vector<std::vector<Variable>> &getEquations() const {
    return Equations;
  }
};