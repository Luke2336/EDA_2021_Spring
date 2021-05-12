#pragma once
#include "Context.hpp"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
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
  std::vector<std::tuple<int, int, int>> dotParse(char *Filename) {
    std::fstream Fin;
    Fin.open(Filename, std::ios::in);
    std::string tmp;
    for (int i = 0; i < 11; ++i)
      getline(Fin, tmp);
    std::map<std::string, int> NameMap;
    NameMap.emplace("\"F0\"", -2);
    while (1) {
      getline(Fin, tmp);
      if (tmp == "{ rank = same; \"CONST NODES\";") {
        getline(Fin, tmp);
        std::string Name = "\"";
        for (int i = tmp.length() - 3; i >= 0; i--) {
          Name += tmp[i];
          if (tmp[i] == '\"')
            break;
        }
        std::reverse(Name.begin(), Name.end());
        NameMap.emplace(Name, -1);
        getline(Fin, tmp);
        assert(tmp == "}");
        getline(Fin, tmp);
        assert(tmp == "}");
        break;
      } else {
        std::string buff;
        int Id;
        std::stringstream ss;
        ss.str(tmp);
        ss >> buff >> buff >> buff >> buff >> buff >> Id >> buff;
        assert(buff == "\";");
        while (1) {
          getline(Fin, tmp);
          if (tmp == "}")
            break;
          tmp.pop_back();
          NameMap.emplace(tmp, Id);
        }
      }
    }
    std::vector<std::tuple<int, int, int>> Ret;
    while (1) {
      getline(Fin, tmp);
      int len = tmp.length();
      if (tmp == "}")
        break;
      if (tmp[len - 2] == ']' && tmp[len - 3] == '\"')
        continue;
      bool pos = tmp[len - 2] == ']';
      while (tmp.back() != '\"')
        tmp.pop_back();
      std::string Par = "", Chd = "";
      std::stringstream ss;
      ss.str(tmp);
      ss >> Par >> tmp >> Chd;
      int P = NameMap[Par];
      int C = NameMap[Chd];
      Ret.emplace_back(P, C, pos);
    }
    Fin.close();
    return Ret;
  }
};