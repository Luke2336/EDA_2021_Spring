#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Nets;
vector<vector<int>> Cells;

void genRandomBit(vector<bool> &v) {
  fill(v.begin(), v.begin() + (v.size() >> 1), 1);
  random_shuffle(v.begin(), v.end());
}

int FM(vector<bool> Partition) {}

int main(int argv, char *argc[]) {
  freopen(argc[1], "r", stdin);
  freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
  srand(time(0));
  int N, M, P = 0;
  cin >> N >> M;
  Nets.resize(M), Cells.resize(N);
  for (int i = 0; i < M; i++) {
    string s;
    getline(cin, s);
    stringstream ss;
    ss.str(s);
    for (int v; ss >> v;)
      Nets[i].push_back(v), Cells[v].push_back(i);
    P += Nets[i].size();
  }
  int run = max(1, (int)2e9 / P);
  vector<vector<bool>> Partition(run, vector<bool>(N));
  vector<int> CntCut;
#pragma omp parallel for
  for (int i = 0; i < run; i++) {
    genRandomBit(Partition[i]);
    CntCut[i] = FM(Partition[i]);
  }
  int ans = 0;
  for (int i = 1; i < run; i++)
    if (CntCut[i] < CntCut[ans])
      ans = i;
  return 0;
}