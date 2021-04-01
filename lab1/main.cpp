#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Nets;
vector<vector<int>> Cells;

inline void genRandomBit(vector<bool> &v) {
  fill(v.begin(), v.begin() + (v.size() >> 1), 1);
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(v.begin(), v.end(), std::default_random_engine(seed));
}

inline bool range(int v, int L, int R) { return L <= v && v <= R; }

class BucketList {
  vector<int> Bucket[2];
  vector<int> Next, Pre;
  int Mx[2];
  int P, n;
  int node_id(int v) { return (Bucket[0].size() << 1) + v; }
  int bucket_id(int b, int id) { return Bucket[0].size() * b + id; }

public:
  BucketList(int P, int n) : P(P), n(n) {
    Mx[0] = Mx[1] = 0;
    int sz = P << 1 | 1;
    Bucket[0].resize(sz, -1), Bucket[1].resize(sz, -1);
    Next.resize(node_id(n)), Pre.resize(node_id(n));
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < sz; ++j)
        Bucket[i][j] = bucket_id(i, j);
  }
  int mx(int b) { return Mx[b]; }
  int pop(int b) {
    int bd = Mx[b];
    int nd = Next[bd];
    Next[bd] = Next[nd];
    if (Next[nd] != -1)
      Pre[Next[nd]] = bd;
    while (Next[bucket_id(b, Mx[b])] == -1)
      --Mx[b];
    Pre[nd] = Next[nd] = -1;
    return nd;
  }
  void remove(int v) {
    int nd = node_id(v);
    Next[Pre[nd]] = Next[nd];
    if (Next[nd] != -1)
      Pre[Next[nd]] = nd;
  }
  void add(int v, int b, int id) {
    int nd = node_id(v);
    int bd = bucket_id(b, id);
    if (Next[bd] != -1)
      Pre[Next[bd]] = nd;
    Next[nd] = Next[bd];
    Next[bd] = nd;
    Pre[nd] = bd;
    Mx[b] = max(Mx[b], id);
  }
};

int FM(vector<bool> Partition, const int P) {
  int N = Cells.size(), M = Nets.size();
  int M1 = ceil(N * 0.45), M2 = floor(N * 0.55);
  vector<bool> Lock(N);
  vector<int> Gain(N), CntCell[2];
  CntCell[0].resize(M), CntCell[1].resize(M);
  for (int i = 0; i < M; i++) {
    for (int j : Nets[i])
      CntCell[Partition[j]][i]++;
    for (int j : Nets[i])
      if (!CntCell[!Partition[j]][i])
        --Gain[j];
      else if (CntCell[Partition[j]][i] == 1)
        ++Gain[j];
  }
  BucketList BL(P, N);
  for (int i = 0; i < N; i++)
    BL.add(i, Partition[i], Gain[i] + P);
  vector<int> sumGain;
  vector<int> swapNode;
  int sz[2] = {N >> 1, N - (N >> 1)};
  for (int t = 0; t < N; ++t) {
    bool b = range(sz[1] - 1, M1, M2) && BL.mx(0) < BL.mx(1) ||
             !range(sz[0] - 1, M1, M2);
    --sz[b], ++sz[!b];
    sumGain.push_back(BL.mx(b) - P);
    int node = BL.pop(b);
    Lock[node] = true;
    swapNode.push_back(node);
    for (int i : Cells[node]) {
      --CntCell[b][i], ++CntCell[!b][i];
      for (int v : Nets[i]) {
        if (Lock[v])
          continue;
        if (!CntCell[b][i] && Partition[v] != b) {
          BL.remove(v);
          BL.add(v, !b, --Gain[v] + P);
        } else if (CntCell[b][i] == 1 && Partition[v] == b) {
          BL.remove(v);
          BL.add(v, b, ++Gain[v] + P);
        }
      }
    }
  }
  int mx_i = 0;
  for (int i = 1; i < sumGain.size(); i++) {
    sumGain[i] += sumGain[i - 1];
    if (sumGain[i] > sumGain[mx_i])
      mx_i = i;
  }
  if (sumGain[mx_i] <= 0)
    return 0;
  for (int i = 0; i <= mx_i; i++)
    Partition[swapNode[i]] = !Partition[swapNode[i]];
  return sumGain[mx_i];
}

int main(int argv, char *argc[]) {
  freopen(argc[1], "r", stdin);
  // freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
  srand(time(0));
  int N, M, P = 0;
  cin >> M >> N;
  Nets.resize(M), Cells.resize(N);
  for (int i = 0; i < M; i++) {
    string s;
    getline(cin, s);
    stringstream ss;
    ss.str(s);
    for (int v; ss >> v;)
      Nets[i].push_back(v - 1), Cells[v - 1].push_back(i);
    P += Nets[i].size();
  }
  // int run = max(1, (int)2e9 / P);
  int run = 1;
  vector<vector<bool>> Partition(run, vector<bool>(N));
  vector<int> CntCut;
#pragma omp parallel for
  for (int i = 0; i < run; i++) {
    genRandomBit(Partition[i]);
    CntCut[i] = FM(Partition[i], P);
  }
  int ans = 0;
  for (int i = 1; i < run; i++)
    if (CntCut[i] < CntCut[ans])
      ans = i;
  for (int i = 0; i < N; i++)
    cout << Partition[ans][i] << '\n';
  return 0;
}