#include "Data.hpp"
#include "Parser.hpp"
#include "RawInput.hpp"
#include "Router.hpp"
#include "RouterContext.hpp"
#include "Timer.hpp"
#include <bits/stdc++.h>
using namespace std;

std::unique_ptr<GlobalTimer> GlobalTimer::uniqueGlobalTimer = nullptr;

int main(int argc, char *argv[]) {

  GlobalTimer::initialTimerAndSetTimeLimit(chrono::seconds(60 * 8));

  if (argc < 3)
    assert(false && "Argument error!!");
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  freopen(argv[1], "r", stdin);
  freopen(argv[2], "w", stdout);

  srand(time(NULL));

  Parser P;
  unique_ptr<RawInput> RawInputPtr = P.parse();

  const int RUN = 16;
  unsigned int seed[RUN];
  for (int i = 0; i < RUN; ++i)
    seed[i] = rand();
  RouterContext Context[RUN];
#pragma omp parallel for
  for (int r = 0; r < RUN; ++r) {
    Context[r] = RouterContext(RawInputPtr.get());
    Router router(&Context[r], seed[r]);
    router.route();
    Context[r].calculateLength();
  }
  RouterContext *BestContext = min_element(Context, Context + RUN);
  BestContext->to_ostream(cout);
  return 0;
}
