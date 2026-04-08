#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n + 1);

  vector<tuple<int, int, long long>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    long long c;
    cin >> a >> b >> c;
    edges[i] = {a, b, c};
    graph[a].push_back(b);
  }

  // We don't need the actual distance, just to know if there is a cycle
  vector<long long> dist(n + 1, 0);
  vector<int> parent(n + 1, -1);
  int cycle_node = -1;
  for (int i = 0; i < n; ++i) {
    cycle_node = -1;
    for (const auto &[u, v, c] : edges) {
      if (dist[u] + c < dist[v]) {
        dist[v] = dist[u] + c;
        parent[v] = u;
        cycle_node = v;
      }
    }
  }

  if (cycle_node == -1) {
    cout << "NO" << "\n";
    return 0;
  }

  int u = cycle_node;
  for (int i = 0; i < n; ++i)
    u = parent[u];

  vector<int> cycle;
  cycle.push_back(u);
  for (int v = parent[u]; v != u; v = parent[v]) {
    cycle.push_back(v);
  }
  cycle.push_back(u);
  reverse(cycle.begin(), cycle.end());
  cout << "YES" << "\n";
  for (int x : cycle)
    cout << x << " ";
  cout << "\n";
}
