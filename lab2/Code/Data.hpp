#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
  Point() : x(-1), y(-1) {}
  Point(int x, int y) : x(x), y(y) {}
  bool operator<(const Point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
  bool operator==(const Point &p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point &p) const { return x != p.x || y != p.y; }
};

struct Block {
  int Left, Right, Up, Down;
  Block() {}
  Block(Point a, Point b)
      : Left(min(a.x, b.x)), Right(max(a.x, b.x)), Up(max(a.y, b.y)),
        Down(min(a.y, b.y)) {}
};

struct Net {
  string Name;
  Point Src, Tar;
  Net() {}
  Net(string Name, Point S, Point T) : Name(Name), Src(S), Tar(T) {}
};