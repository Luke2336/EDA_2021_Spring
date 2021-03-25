#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Nets;
vector<vector<int>> Cells;

inline void genRandomBit(vector<bool> &v) {
  fill(v.begin(), v.begin() + (v.size() >> 1), 1);
  random_shuffle(v.begin(), v.end());
}

inline bool range(int v, int L, int R) { return L <= v && v <= R; }

int FM(vector<bool> Partition, const int P) {
  int N = Cells.size(), M = Nets.size();
  int M1 = ceil(N * 0.45), M2 = floor(N * 0.55);
  vector<bool> Lock(N);
  vector<int> Gain(N);
  vector<int> CntCell[2];
  CntCell[0].resize(M);
  CntCell[1].resize(M);
  for (int i = 0; i < M; i++) {
    for (int j : Nets[i])
      CntCell[Partition[j]][i]++;
    for (int j : Nets[i])
      if (!CntCell[!Partition[j]][i])
        Gain[j]--;
      else if (CntCell[Partition[j]][i] == 1)
        Gain[j]++;
  }
  vector<int> Bucket[2];
  vector<int> CntBucket[2];
  int szBucket = P << 1 | 1;
  Bucket[0].resize(szBucket);
  Bucket[1].resize(szBucket);
  CntBucket[0].resize(szBucket);
  CntBucket[1].resize(szBucket);
  auto id = [](int i, int sz) { return (sz << 1) + i; };
  auto reId = [](int i, int sz) { return i - (sz << 1); };
  vector<int> Next(id(N, szBucket), -1);
  vector<int> Pre(id(N, szBucket), -1);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < szBucket; j++)
      Bucket[i][j] = (i ? szBucket : 0) + j;
  int mx[2] = {0, 0};
  for (int i = 0; i < N; i++) {
    int g = Gain[i] + P, p = Partition[i];
    int idCell = id(i, szBucket);
    int idBucket = p ? szBucket + g : g;
    mx[p] = max(mx[p], g);
    CntBucket[p][g]++;
    if (Next[idBucket] != -1)
      Pre[Next[idBucket]] = idCell, Next[idCell] = Next[idBucket];
    Next[idBucket] = idCell, Pre[idCell] = idBucket;
  }
  vector<int> sumGain;
  vector<int> swapNode;
  int sz[2] = {N >> 1, N - (N >> 1)};
  for (int t = 0; t < N; t++) {
    bool b =
        range(sz[1] - 1, M1, M2) && mx[0] < mx[1] || !range(sz[0] - 1, M1, M2);
    sz[b]--, sz[!b]++;
    sumGain.push_back(mx[b] - P);
    int idBucket = b ? szBucket + mx[b] : mx[b];
    int idCell = Next[idBucket];
    int node = reId(idCell, szBucket);
    Lock[node] = true;
    swapNode.push_back(node);
    Next[idBucket] = Next[idCell];
    if (Next[idCell] != -1)
      Pre[Next[idCell]] = idBucket;
    while (Next[b ? szBucket + mx[b] : mx[b]] == -1 && mx[b])
      mx[b]--;
    for (int i : Cells[node]) {
      CntCell[b][i]--, CntCell[!b][i]++;
      for (int v : Nets[i]) {
        if (Lock[v])
          continue;
        if (!CntCell[b][i] && Partition[v] != b) {
          // 右邊 node 的 Gain--
          CntBucket[!b][Gain[v]]--;
          CntBucket[!b][--Gain[v]]++;
          int idV = id(v, szBucket);
          Next[Pre[idV]] = Next[idV];
          if (Next[idV])
            Pre[Next[idV]] = Pre[idV];
          int idB = b ? Gain[v] : szBucket + Gain[v];
          Next[idV] = Next[idB], Pre[Next[idB]] = idV;
          Pre[idV] = idB, Next[idB] = idV;
          mx[!b] = max(mx[!b], Gain[v]);
        } else if (CntCell[b][i] == 1 && Partition[v] == b) {
          // 左邊 node 的 Gain++
          CntBucket[b][Gain[v]]--;
          CntBucket[b][++Gain[v]]++;
          int idV = id(v, szBucket);
          Next[Pre[idV]] = Next[idV];
          if (Next[idV])
            Pre[Next[idV]] = Pre[idV];
          int idB = b ? szBucket + Gain[v] : Gain[v];
          Next[idV] = Next[idB], Pre[Next[idB]] = idV;
          Pre[idV] = idB, Next[idB] = idV;
          mx[b] = max(mx[b], Gain[v]);
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
  freopen("output.txt", "w", stdout);
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
  int run = max(1, (int)2e9 / P);
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
  return 0;
}