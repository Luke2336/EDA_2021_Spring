#pragma once
#include "Grid.hpp"
#include "RawInput.hpp"
#include <bits/stdc++.h>
using namespace std;

class Router {
  RawInput *RawInputPtr;
  GridContent G;
  // vector<vector<Point>> Path();
  const int dx[4] = {-1, 1, 0, 0};
  const int dy[4] = {0, 0, -1, 1};
  bool inRange(Point P) {
    return 0 <= P.x && P.x <= RawInputPtr->Col && 0 <= P.y &&
           P.y <= RawInputPtr->Row;
  }

public:
  Router() {}
  Router(RawInput *R) : RawInputPtr(R), G(R) {}
  void init() {
    int Col = RawInputPtr->Col, Row = RawInputPtr->Row;
    vector<vector<Point>> Par(Col, vector<Point>(Row));
    for (auto &net : RawInputPtr->Nets) {
      vector<vector<double>> Dist(
          Col, vector<double>(Row, numeric_limits<double>::infinity()));
      Dist[net.Src.x][net.Src.y] = 0;
      queue<Point> q;
      q.emplace(net.Src);
      // BFS
      while (!q.empty()) {
        auto P = q.front();
        q.pop();
        if (P == net.Tar)
          break;
        for (int di = 0; di < 4; ++di) {
          Point NP(P.x + dx[di], P.y + dy[di]);
          if (!inRange(NP))
            continue;
          if (Dist[P.x][P.y] + 1 < Dist[NP.x][NP.y]) {
            Dist[NP.x][NP.y] = Dist[P.x][P.y] + 1;
            Par[NP.x][NP.y] = P;
            q.push(NP);
          }
        }
      }
      // Backtracking
      Point P = net.Tar;
      while (P != net.Src) {
        G.Grids[P.x][P.y].Nets.emplace(&net);
      }
    }
  }
  void reroute() {}
};