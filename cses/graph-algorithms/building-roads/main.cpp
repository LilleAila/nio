#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

struct DSU {
  vector<int> parent;
  vector<int> size;

  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
  }

  int find(int i) {
    // Find the set a node belongs to
    if (parent[i] == i)
      return i;
    // Path compression
    return parent[i] = find(parent[i]);
  }

  bool combine(int i, int j) {
    // Find the roots of the two
    int root_i = find(i);
    int root_j = find(j);

    // Check whether or not they are already combined
    if (root_i != root_j) {
      // Union by size
      if (size[root_i] < size[root_j]) {
        swap(root_i, root_j);
      }
      parent[root_j] = root_i;
      size[root_i] += size[root_j];
      return true;
    } else {
      return false;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  DSU dsu(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    dsu.combine(a, b);
  }

  // Basically a variant of kruskal's MST
  // We already have groups of "islands" and can
  // add edges from 1->i to combine the islands.

  vector<pair<int, int>> edges;
  for (int i = 2; i <= n; i++) {
    if (dsu.combine(1, i)) {
      edges.push_back({1, i});
    }
  }

  cout << edges.size() << endl;
  for (const auto &[a, b] : edges)
    cout << a << " " << b << endl;
}
