#pragma once
#include "Data.hpp"
#include "RawInput.hpp"
#include <bits/stdc++.h>
using namespace std;

struct Grid {
  unordered_set<Net *> Nets;
  Grid() {}
};

struct GridContent {
  vector<vector<Grid>> Grids;
  GridContent() {}
  GridContent(RawInput *RawInputPtr) {
    Grids.resize(RawInputPtr->Col, vector<Grid>(RawInputPtr->Row));
  }
};