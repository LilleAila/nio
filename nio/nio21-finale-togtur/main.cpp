#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

const int INF = std::numeric_limits<int>::max();

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, v;
  cin >> n >> m >> v;

  vector<vector<pair<int, int>>> graph(n);
  for (int i = 0; i < m; i++) {
    int a, b, k;
    cin >> a >> b >> k;
    graph[a].push_back({b, k});
    graph[b].push_back({a, k});
  }

  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                 greater<tuple<int, int, int>>>
      pq;
  vector<vector<int>> dist(n, vector<int>(v + 1, INF));

  pq.push({0, 0, v});
  dist[0][v] = 0;

  while (!pq.empty()) {
    auto [c, u, b] = pq.top();
    pq.pop();

    if (c > dist[u][b]) {
      continue;
    }

    if (u == 1) {
      cout << c << endl;
      return 0;
    }

    for (const auto &[v, cost] : graph[u]) {
      int new_cost = c + cost;
      if (new_cost < dist[v][b]) {
        dist[v][b] = new_cost;
        pq.push({new_cost, v, b});
      }

      if (b > 0 && c < dist[v][b - 1]) {
        dist[v][b - 1] = c;
        pq.push({c, v, b - 1});
      }
    }
  }
}
