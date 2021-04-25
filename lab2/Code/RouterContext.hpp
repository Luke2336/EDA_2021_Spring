#pragma once
#include "Data.hpp"
#include "RawInput.hpp"
#include <bits/stdc++.h>
using namespace std;

struct Grid {
  unordered_set<const Net *> Nets;
  bool IsBlock;
  Grid() : IsBlock(false) {}
};

struct RouterContext {
  vector<vector<Grid>> Grids;
  unordered_map<const Net *, vector<Grid *>> GridInNet;
  const RawInput *RawInputPtr;

  RouterContext() : RawInputPtr(nullptr) {}

  RouterContext(const RawInput *RawInputPtr) : RawInputPtr(RawInputPtr) {
    Grids.resize(RawInputPtr->Col, vector<Grid>(RawInputPtr->Row));
    for (auto Block : RawInputPtr->Blocks) {
      for (int x = Block.Left; x <= Block.Right; ++x)
        for (int y = Block.Down; y <= Block.Up; ++y)
          Grids[x][y].IsBlock = true;
    }
  }

  void addNet(const Net *NetPtr, vector<Grid *> &&Path) {
    for (auto GridPtr : Path)
      GridPtr->Nets.insert(NetPtr);
    GridInNet[NetPtr] = move(Path);
  }

  void removeNet(const Net *NetPtr) {
    for (auto GridPtr : GridInNet[NetPtr])
      GridPtr->Nets.erase(NetPtr);
    GridInNet.erase(NetPtr);
  }

  int overflow() {
    int Cnt = 0;
    for (auto v : Grids) {
      for (auto &g : v) {
        Cnt += (g.Nets.size() > 1) ? (g.Nets.size() - 1) : 0;
      }
    }
    return Cnt;
  }
};