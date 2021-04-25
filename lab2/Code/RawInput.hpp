#pragma once
#include "Data.hpp"
#include <bits/stdc++.h>
using namespace std;

struct RawInput {
  const int Row, Col;
  const vector<Block> Blocks;
  const vector<Net> Nets;
  RawInput(int R, int C, vector<Block> &&Blocks, vector<Net> &&Nets)
      : Row(R), Col(C), Blocks(move(Blocks)), Nets(move(Nets)) {}
};