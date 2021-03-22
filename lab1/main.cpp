#include <bits/stdc++.h>
using namespace std;
#define RUNS 20

void genRandomBit(vector<bool> &v, const int sz) {
	v.resize(sz >> 1, 1);
	v.resize(sz);
	random_shuffle(v.begin(), v.end());
}


int main(int argv, char *argc[]) {
  freopen(argc[1], "r", stdin);
  freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
	srand(time(0));
  // Read Input
  int N, M;
  cin >> N >> M;
  vector<vector<int>> Nets(M);
  for (int i = 0; i < M; i++) {
    string s;
    getline(cin, s);
    stringstream ss;
    ss.str(s);
    for (int v; ss >> v;)
      Nets[i].push_back(v);
  }
	vector<bool> Partition[RUNS];
#pragma omp parallel for
  for (int i = 0; i < RUNS; i++) {
		genRandomBit(Partition[i], N);
		
  }
  return 0;
}