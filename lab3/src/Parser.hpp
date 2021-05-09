#pragma once
#include "Context.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

class Parser {
public:
  void parser(double Prob[26], std::vector<std::vector<Variable>> &Clauses,
              std::vector<int> &Vars) {
    Clauses.clear();
    while (Clauses.empty()) {
      std::string Tmp;
      std::getline(std::cin, Tmp);
      std::vector<Variable> EmptyVector;
      Clauses.push_back(EmptyVector);
      for (int i = 0; Tmp[i]; ++i) {
        if (Tmp[i] == '+')
          Clauses.emplace_back(EmptyVector);
        else if (isupper(Tmp[i]))
          Clauses.back().emplace_back(Tmp[i] - 'A', true);
        else if (islower(Tmp[i]))
          Clauses.back().emplace_back(Tmp[i] - 'a', false);
      }
      if (Clauses.back().empty())
        Clauses.emplace_back();
    }
    bool IsVar[26] = {};
    int ch;
    double p;
    while (std::cin >> ch >> p) {
      if (isupper(ch))
        Prob[ch - 'A'] = p, IsVar[ch - 'A'] = true;
      else
        Prob[ch - 'a'] = 1 - p, IsVar[ch - 'a'] = true;
    }
    Vars.clear();
    for (int i = 0; i < 26; ++i)
      if (IsVar[i])
        Vars.emplace_back(i);
  }
};