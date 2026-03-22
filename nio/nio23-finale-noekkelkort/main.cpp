#include <bitset>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

using Permission = bitset<30>;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k, t;
  cin >> n >> m >> k >> t;

  int j = 0;
  vector<tuple<int, int, Permission>> connections(t);
  vector<vector<pair<int, Permission>>> graph(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    Permission k;
    cin >> u >> v >> k;

    graph[u].push_back({v, k});
    graph[v].push_back({u, k});

    if (j < t) {
      connections[i] = {u, v, k};
    }
    j++;
  }

  // O(t (n + m))
  for (const auto &[u, v, k] : connections) {
    deque<int> queue;
    vector<bool> visited(n);
    Permission permission = ~k;
    queue.push_back(u);
    visited[u] = true;

    while (!queue.empty()) {
      int a = queue.front();
      queue.pop_front();

      if (a == v) {
        cout << "0" << endl;
        goto valid;
      }

      for (const auto &[b, k] : graph[a]) {
        if (!visited[b] && (permission & k).any()) {
          queue.push_back(b);
          visited[b] = true;
        }
      }
    }

    cout << "1" << endl;
  valid:;
  }
}
