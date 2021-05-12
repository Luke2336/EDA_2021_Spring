#pragma once
#include "Context.hpp"
#include <algorithm>
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
  std::map<std::string, int> NameMap;
  std::map<int, int> LevelMap;

  void parser(double *Prob, std::vector<std::vector<Variable>> &Clauses,
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
        Clauses.pop_back();
    }
    bool IsVar[26] = {};
    char ch;
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
    NameMap.emplace("\"F0\"", 0);
    LevelMap.emplace(0, -2);
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
        NameMap.emplace(Name, NameMap.size());
        LevelMap.emplace(NameMap[Name], -1);
        getline(Fin, tmp);
        tmp.pop_back();
        NameMap.emplace(tmp, NameMap.size());
        LevelMap.emplace(NameMap[tmp], -1);
        getline(Fin, tmp);
        getline(Fin, tmp);
        break;
      } else {
        std::string buff;
        int Id;
        std::stringstream ss;
        ss.str(tmp);
        ss >> buff >> buff >> buff >> buff >> buff >> Id >> buff;
        while (1) {
          getline(Fin, tmp);
          if (tmp == "}")
            break;
          tmp.pop_back();
          if (NameMap.count(tmp) == 0)
            NameMap.emplace(tmp, NameMap.size());
          LevelMap.emplace(NameMap[tmp], Id);
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
      bool pos = tmp[len - 4] != 'e';
      while (tmp.back() != '\"')
        tmp.pop_back();
      std::string Par = "", Chd = "";
      std::stringstream ss;
      ss.str(tmp);
      ss >> Par >> tmp >> Chd;
      Ret.emplace_back(NameMap[Par], NameMap[Chd], pos);
    }
    Fin.close();
    return Ret;
  }
};