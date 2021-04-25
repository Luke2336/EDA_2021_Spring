#pragma once
#include "Data.hpp"
#include "RawInput.hpp"
#include <bits/stdc++.h>
using namespace std;

struct Grid {
  int x, y;
  unordered_set<const Net *> Nets;
  bool IsBlock;
  Grid() : IsBlock(false) {}
};

struct RouterContext {
  bool FinishRoute;
  vector<vector<Grid>> Grids;
  unordered_map<const Net *, vector<Grid *>> GridInNet;
  long long Length;
  const RawInput *RawInputPtr;

  RouterContext() : FinishRoute(false), RawInputPtr(nullptr) {
    calculateLength();
  }

  RouterContext(const RawInput *RawInputPtr)
      : FinishRoute(false), RawInputPtr(RawInputPtr) {
    Grids.resize(RawInputPtr->Col, vector<Grid>(RawInputPtr->Row));
    for (int x = 0; x < RawInputPtr->Col; ++x)
      for (int y = 0; y < RawInputPtr->Row; ++y)
        Grids[x][y].x = x, Grids[x][y].y = y;
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

  int overflow() const {
    int Cnt = 0;
    for (const auto &v : Grids)
      for (const auto &g : v)
        Cnt += (g.Nets.size() > 1) ? (g.Nets.size() - 1) : 0;
    return Cnt;
  }

  void calculateLength() {
    Length = 0;
    for (auto &NT : GridInNet) {
      Length += NT.second.size();
    }
    if (!FinishRoute)
      Length = numeric_limits<long long>().max();
  }

  bool operator<(const RouterContext &R) const { return Length < R.Length; }

  void to_ostream(ostream &out) const {
    for (auto &NT : GridInNet) {
      auto &NetPtr = NT.first;
      out << NetPtr->Name << '\n';
      out << "begin\n";
      out << NT.second.size() - 2 << '\n';
      auto &Path = NT.second;
      for (size_t i = 1; i < Path.size(); ++i)
        out << Path[i - 1]->x << ' ' << Path[i - 1]->y << ' ' << Path[i]->x
            << ' ' << Path[i]->y << '\n';
      out << "end\n";
    }
  }
};