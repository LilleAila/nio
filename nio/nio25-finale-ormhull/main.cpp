#include <iostream>
#include <climits>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k, a, b;
  cin >> n >> m >> k >> a >> b;

  vector<vector<tuple<int, int>>> graph(n);
  while (m--) {
    int v, u, t;
    cin >> v >> u >> t;
    graph[v].push_back({u, t});
    graph[u].push_back({v, t});
  }

  vector<bool> wormhole(n);
  while (k--) {
    int i;
    cin >> i;
    wormhole[i] = true;
  }

  priority_queue<tuple<int, int>, deque<tuple<int, int>>, greater<tuple<int, int>>> pq;
  vector<int> dist(n, INT_MAX);

  dist[a] = 0;
  pq.push({0, a});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (u == b) {
      break;
    }

    for (const auto &[v, t] : graph[u]) {
      int new_dist = d + t;
      if (new_dist < dist[v]) {
	dist[v] = new_dist;
        pq.push({new_dist, v});
      }
    }
  }

  if (dist[b] != INT_MAX) {
    cout << dist[b] << endl;
  } else {
    cout << "-1" << endl;
  }
}
