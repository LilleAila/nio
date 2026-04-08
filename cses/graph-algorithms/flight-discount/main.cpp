#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

const long long INF = LLONG_MAX / 3;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, long long>>> graph(n + 1);
  while (m--) {
    int a, b;
    long long c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
  }

  // {used_ticket, dist, node}
  priority_queue<tuple<long long, bool, int>,
                 vector<tuple<long long, bool, int>>,
                 greater<tuple<long long, bool, int>>>
      pq;
  vector<array<long long, 2>> dist(n + 1, {INF, INF});
  dist[1][false] = 0;
  pq.push({0, false, 1});

  while (!pq.empty()) {
    auto [d, used, u] = pq.top();
    pq.pop();

    if (d > dist[u][used])
      continue;

    for (const auto &[v, c] : graph[u]) {
      long long new_cost = d + c;
      if (new_cost < dist[v][used]) {
        dist[v][used] = new_cost;
        pq.push({new_cost, used, v});
      }

      if (!used) {
        long long cost_use = d + c / 2;
        if (cost_use < dist[v][true]) {
          dist[v][true] = cost_use;
          pq.push({cost_use, true, v});
        }
      }
    }
  }

  cout << min(dist[n][false], dist[n][true]) << "\n";
}
