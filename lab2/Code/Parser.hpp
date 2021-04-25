#pragma once
#include<bits/stdc++.h>
#include "Data.hpp"
#include "RawInput.hpp"
using namespace std;

class Parser {
public:
  Parser() {}
  unique_ptr<RawInput> parse() {
    string buff;
    cin >> buff;
    assert(buff == ".row");
    int Row, Col;
    cin >> Row;
    cin >> buff;
    assert(buff == ".col");
    cin >> Col;
    cin >> buff;
    assert(buff == ".blk");
    int NumBlk;
    cin >> NumBlk;
    vector<Block> Blocks;
    for (int i = 0; i < NumBlk; ++i) {
      int L, D, R, U;
      cin >> L >> D >> R >> U;
      Blocks.emplace_back(Point(L, D), Point(R, U));
    }
    cin >> buff;
    assert(buff == ".net");
    int NumNet;
    cin >> NumNet;
    vector<Net> Nets;
    for (int i = 0; i < NumNet; ++i) {
      string name;
      int x1, y1, x2, y2;
      cin >> name >> x1 >> y1 >> x2 >> y2;
      Nets.emplace_back(name, Point(x1, y1), Point(x2, y2));
    }
    return make_unique<RawInput>(Row, Col, move(Blocks), move(Nets));
  }
};