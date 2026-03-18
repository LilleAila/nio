// This version should fix the issues with the previous iteration by using a fenwick tree.

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
  int n;
  vector<long long> bit;

  Fenwick(int n) {
    this->n = n;
    bit.assign(n + 1, 0);
  }

  void add(int i, long long v) {
    for (i++; i < n; i += i & -i) bit[i] += v;
  }

  long long sum(int i) {
    long long s = 0;
    for (i++; i > 0; i -= i & -i) s += bit[i];
    return s;
  }

  long long sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  string line;
  cin >> line;

  vector<int> xs;
  for (char c : line) {
    int i = c - 'a';
    xs.push_back(i);
  }

  vector<vector<int>> indexes(k);
  for (int i = 0; i < xs.size(); i++) {
    int v = xs[i];
    indexes[v].push_back(i);
  }

  vector<pair<int, int>> pairs;
  for (int t = 0; t < indexes.size(); t++) {
    vector<int> is = indexes[t];
    int mid = is.size() / 2;
    for (int i = 0; i < mid; i++) {
      pairs.push_back({is[i], is[mid + i]});
    }
  }
  sort(pairs.begin(), pairs.end());

  Fenwick fw(n);
  long long shorts = 0;
  for (const auto& p : pairs) {
    fw.add(p.second, 1);
    shorts += fw.sum(p.first, p.second - 1);
  }

  cout << shorts << endl;
}
