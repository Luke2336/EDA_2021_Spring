#pragma once
#include<bits/stdc++.h>
using namespace std;

class GlobalTimer {
  static unique_ptr<GlobalTimer> uniqueGlobalTimer;
  chrono::seconds timeLimit;
  chrono::high_resolution_clock::time_point startTime;

  GlobalTimer() {}
  void restart(chrono::seconds seconds) {
    timeLimit = seconds;
    startTime = chrono::high_resolution_clock::now();
  }

public:
  static void initialTimerAndSetTimeLimit(chrono::seconds seconds) {
    if (uniqueGlobalTimer == nullptr)
      uniqueGlobalTimer = unique_ptr<GlobalTimer>(new GlobalTimer);
    uniqueGlobalTimer->restart(seconds);
  }
  static GlobalTimer *getInstance() { return uniqueGlobalTimer.get(); }
  template <class ToDuration = chrono::nanoseconds>
  ToDuration getDuration() {
    auto endTime = chrono::high_resolution_clock::now();
    return chrono::duration_cast<ToDuration>(endTime - startTime);
  }
  bool overTime() { return getDuration<>() >= timeLimit; }
};