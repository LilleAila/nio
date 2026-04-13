#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;

struct DSU {
  vector<int> size;
  vector<int> parent;

  DSU(int n) : size(n, 1), parent(n) { iota(parent.begin(), parent.end(), 0); }

  int find(int i) {
    if (parent[i] == i)
      return i;
    else
      return parent[i] = find(parent[i]);
  }

  bool unite(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b)
      return false;
    if (size[b] > size[a])
      swap(root_a, root_b);

    parent[root_b] = root_a;
    size[root_a] += size[root_b];

    return true;
  }

  int get_size(int i) { return size[find(i)]; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<tuple<ll, int, int>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    edges.push_back({c, a, b});
  }

  sort(edges.begin(), edges.end());

  DSU dsu(n + 1);
  ll result = 0;
  for (const auto &[c, a, b] : edges) {
    if (dsu.unite(a, b))
      result += c;
  }

  if (dsu.get_size(1) == n)
    cout << result << "\n";
  else
    cout << "IMPOSSIBLE" << "\n";
}
