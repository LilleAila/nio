#include <iostream>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <vector>
using namespace std;

struct DSU {
  vector<int> parent, size;

  DSU(int n) {
    size.assign(n, 1);
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int n) {
    if (n == parent[n]) return n;
    return parent[n] = find(parent[n]);
  }

  void join(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (size[rv] > size[ru]) swap(ru, rv);
    parent[rv] = ru;
    size[rv] += size[ru];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n, q;
  cin >> n >> q;

  DSU dsu(n);

  while (q--) {
    char action;
    int a, b;
    cin >> action >> a >> b;

    if (action == '=') dsu.join(a, b);
    else cout << (dsu.find(a) == dsu.find(b) ? "yes" : "no") << "\n";
  }
}
