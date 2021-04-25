#pragma once
#include "RouterContext.hpp"
#include <bits/stdc++.h>
using namespace std;

class Router {
  RouterContext *ContextPtr;
  unsigned RandSeed;

  vector<Grid *> routeOneNet(const Net *NetPtr) {
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    priority_queue<pair<double, Point>, vector<pair<double, Point>>,
                   greater<pair<double, Point>>>
        PQ;
    int Row = ContextPtr->RawInputPtr->Row, Col = ContextPtr->RawInputPtr->Col;
    auto INF_DOUBLE = numeric_limits<double>().infinity();
    vector<vector<double>> Dis(Col, vector<double>(Row, INF_DOUBLE));
    vector<vector<Point>> Par(Col, vector<Point>(Row));
    auto cost = [&](Point P) {
      const auto &Grid = ContextPtr->Grids[P.x][P.y];
      double overflow = Grid.Nets.size();
      const double parameter = Row * Col; // TODO
      return parameter * overflow * overflow;
    };
    Dis[NetPtr->Src.x][NetPtr->Src.y] = 0;
    PQ.emplace(0, NetPtr->Src);
    while (!PQ.empty()) {
      Point P = PQ.top().second;
      double OldDis = PQ.top().first;
      PQ.pop();
      if (P == NetPtr->Tar)
        break;
      if (OldDis > Dis[P.x][P.y])
        continue;
      for (int di = 0; di < 4; ++di) {
        int NewX = P.x + dx[di];
        int NewY = P.y + dy[di];
        Point NewP(NewX, NewY);
        auto inRange = [&](int x, int limit) { return 0 <= x && x < limit; };
        if (!inRange(NewX, Col) || !inRange(NewY, Row))
          continue;
        double NewDis = Dis[P.x][P.y] + 1 + cost(NewP);
        if (NewDis < Dis[NewX][NewY]) {
          Dis[NewX][NewY] = NewDis;
          Par[NewX][NewY] = P;
          PQ.emplace(NewDis, NewP);
        }
      }
    }
    vector<Grid *> Path;
    for (Point tmp = NetPtr->Tar;; tmp = Par[tmp.x][tmp.y]) {
      Path.emplace_back(&ContextPtr->Grids[tmp.x][tmp.y]);
      if (tmp == NetPtr->Src)
        break;
    }
    return Path;
  }

  static bool cmp(const Net *a, const Net *b) {
    auto weight = [&](const Net *n) {
      return abs(n->Src.x - n->Tar.x) + abs(n->Src.y - n->Tar.y);
    };
    return weight(a) < weight(b);
  }

  void firstRoute() { // TODO
    vector<const Net *> NetPtrs(ContextPtr->RawInputPtr->Nets.size());
    for (size_t i = 0; i < ContextPtr->RawInputPtr->Nets.size(); ++i)
      NetPtrs[i] = &ContextPtr->RawInputPtr->Nets[i];
    shuffle(NetPtrs.begin(), NetPtrs.end(), default_random_engine(RandSeed));
    sort(NetPtrs.begin(), NetPtrs.end(), cmp);
    for (auto NetPtr : NetPtrs) {
      ContextPtr->addNet(NetPtr, routeOneNet(NetPtr));
    }
  }

  bool reroute() {
    // TODO
  }

public:
  Router(RouterContext *ContextPtr, int seed)
      : ContextPtr(ContextPtr), RandSeed(seed) {}

  bool route() { // TODO
    firstRoute();
  }
};