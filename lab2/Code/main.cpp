#include "Parser.hpp"
#include "RawInput.hpp"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3)
    assert(false && "Argument error!!");
  freopen(argv[1], "r", stdin);
  freopen(argv[2], "w", stdout);
  Parser P;
  unique_ptr<RawInput> RawInputPtr = P.parse();
  return 0;
}