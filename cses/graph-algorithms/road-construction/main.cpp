#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct DSU {
  vector<int> parent;
  vector<int> size;
  int components;
  int largest_component = 1;

  DSU(int n) : parent(n), size(n, 1), components(n) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i)
      return i;
    return parent[i] = find(parent[i]);
  }

  bool unite(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);

    if (root_a == root_b)
      return false;
    if (size[root_b] > size[root_a])
      swap(root_a, root_b);

    parent[root_b] = root_a;
    size[root_a] += size[root_b];

    components--;
    if (size[root_a] > largest_component)
      largest_component = size[root_a];

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  DSU dsu(n + 1);
  while (m--) {
    int a, b;
    cin >> a >> b;

    dsu.unite(a, b);
    cout << dsu.components - 1 << " " << dsu.largest_component << "\n";
  }
}
