#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Nets;
vector<vector<int>> Cells;
class BucketList {
  // vector<int> Next, Pre;
  int P, maxP, n, Mx[2];
  // int node_id(int v) { return (maxP << 1) + v; }
  // int node_reid(int i) { return i - (maxP << 1); }
  // int bucket_id(int b, int id) { return b ? maxP + id : id; }

  map<int, unordered_set<int>> mp[2];
  unordered_map<int, pair<int, int>> Gain;

public:
  BucketList(int P, int n) : P(P), n(n), maxP((P << 1) | 1) {
    // Mx[0] = Mx[1] = -1;
    // Next.resize((maxP << 1) + n, -1);
    // Pre.resize(Next.size(), -1);
  }
  int mx(int b) {
    while (mp[b].size() && mp[b].rbegin()->second.empty())
      mp[b].erase(mp[b].rbegin()->first);
    if (mp[b].size() == 0) return -1;
    assert(mp[b].size() > 0);
    return mp[b].rbegin()->first;
    // while (Mx[b] > 0 && Next[bucket_id(b, Mx[b])] == -1)
    //   --Mx[b];
    // return Mx[b];
  }
  int pop(int b) {
    if (mx(b) < 0) return -1;
    assert(mp[b].count(mx(b)));
    int ret = *(mp[b].at(mx(b)).begin());
    mp[b].at(mx(b)).erase(ret);
    return ret;
    // int bd = bucket_id(b, mx(b));
    // int nd = Next[bd];
    // if (nd < 0)
    //   return -1;
    // Next[bd] = Next[nd];
    // if (Next[nd] != -1)
    //   Pre[Next[nd]] = bd;
    // Pre[nd] = Next[nd] = -1;
    // return node_reid(nd);
  }
  void remove(int v) {
    assert(Gain.count(v));
    assert(mp[Gain.at(v).first].count(Gain.at(v).second));
    mp[Gain.at(v).first].at(Gain.at(v).second).erase(v);
    // int nd = node_id(v);
    // Next[Pre[nd]] = Next[nd];
    // if (Next[nd] != -1)
    //   Pre[Next[nd]] = nd;
  }
  void add(int v, int b, int id) {
    Gain[v] = make_pair(b, id);
    mp[b][id].insert(v);
    // int nd = node_id(v);
    // int bd = bucket_id(b, id);
    // if (Next[bd] != -1)
    //   Pre[Next[bd]] = nd;
    // Next[nd] = Next[bd];
    // Next[bd] = nd;
    // Pre[nd] = bd;
    // Mx[b] = max(Mx[b], id);
  }
};
inline bool range(int v, int L, int R) { return L <= v && v <= R; }
int FM(vector<bool> &Partition, const int P) {
  int N = Cells.size(), M = Nets.size();
  int M1 = ceil(N * 0.46), M2 = floor(N * 0.54);
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
    bool b;
    if (range(sz[0] - 1, M1, M2) && BL.mx(0) >= BL.mx(1))
      b = 0;
    else if (range(sz[0] + 1, M1, M2) && BL.mx(0) <= BL.mx(1))
      b = 1;
    else if (range(sz[0] - 1, M1, M2))
      b = 0;
    else if (range(sz[0] + 1, M1, M2))
      b = 1;
    else
      break;
    --sz[b], ++sz[!b];
    sumGain.push_back(BL.mx(b) - P);
    int node = BL.pop(b);
    if (node < 0)
      break;
    Lock[node] = true;
    swapNode.push_back(node);
    for (int i : Cells[node]) {
      --CntCell[b][i], ++CntCell[!b][i];
      for (int v : Nets[i]) {
        if (Lock[v])
          continue;
        if (!CntCell[b][i] && Partition[v] != b) {
          BL.remove(v);
          BL.add(v, !b, (--Gain[v]) + P);
        } else if (CntCell[b][i] == 1 && Partition[v] == b) {
          BL.remove(v);
          BL.add(v, b, (++Gain[v]) + P);
        }
      }
    }
  }
  int mx_i = 0;
  for (int i = 1; i < sumGain.size(); ++i) {
    sumGain[i] += sumGain[i - 1];
    if (sumGain[i] > sumGain[mx_i])
      mx_i = i;
  }
  if (sumGain.size() && sumGain[mx_i] > 0)
    for (int i = 0; i <= mx_i; ++i)
      Partition[swapNode[i]] = !Partition[swapNode[i]];
  int ret = 0;
  for (int i = 0; i < M; ++i) {
    bool cut = false;
    for (int v : Nets[i])
      if (Partition[v] != Partition[Nets[i][0]])
        cut = true;
    ret += cut;
  }
  return ret;
}
unsigned seed = 112098;
inline void genRandomBit(vector<bool> &v) {
  fill(v.begin(), v.begin() + (v.size() >> 1), 1);
  shuffle(v.begin(), v.end(), std::default_random_engine(seed));
}
int main(int argv, char *argc[]) {
  freopen(argc[1], "r", stdin);
  freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(0), cin.tie(0);
  // seed = std::chrono::system_clock::now().time_since_epoch().count();
  int N, M, P = 0;
  cin >> M >> N;
  Nets.resize(M), Cells.resize(N);
  for (int i = 0; i < M; ++i) {
    string s;
    getline(cin, s);
    stringstream ss;
    ss.str(s);
    for (int v; ss >> v;)
      Nets[i].push_back(v - 1), Cells[v - 1].push_back(i);
    P += Nets[i].size();
  }
  int run = 16;
  vector<vector<bool>> Partition(run, vector<bool>(N));
  vector<int> CntCut(run, M + 10);
#pragma omp parallel for
  for (int i = 0; i < run; ++i) {
    vector<bool> tmp(N);
    genRandomBit(tmp);
    for (int k = 0; k < 50; ++k) {
      int cut = FM(tmp, P);
      if (cut < CntCut[i])
        CntCut[i] = cut, Partition[i] = tmp;
    }
  }
  int ans = 0;
  for (int i = 1; i < run; ++i)
    if (CntCut[i] < CntCut[ans])
      ans = i;
  for (int i = 0; i < N; ++i)
    cout << Partition[ans][i] << '\n';
  return 0;
}
