#include <iostream>
#include <functional>
#include <tuple>
#include <queue>
#include <utility>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX / 4;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> price(n);
  for (int i = 0; i < n; ++i)
    cin >> price[i];

  vector<vector<pair<int, int>>> graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v, d;
    cin >> u >> v >> d;
    graph[u].push_back({v, d});
    graph[v].push_back({u, d});
  }

  int q;
  cin >> q;

  while (q--) {
    int c, s, e;
    cin >> c >> s >> e;

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    vector<vector<int>> dp(n, vector<int>(c+1, INF));
    dp[s][0] = 0;
    pq.push({0, s, 0});

    int result = -1;

    while (!pq.empty()) {
      const auto [dist, u, fuel] = pq.top();
      pq.pop();

      if (u == e) {
        result = dist;
        break;
      }

      if (dist > dp[u][fuel]) continue;

      for (const auto &[v, d] : graph[u]) {
        if (d > fuel) continue;
        int new_fuel = fuel - d;
        int new_dist = dist;
        dp[v][new_fuel] = min(dp[v][new_fuel], new_dist);
        pq.push({new_dist, v, new_fuel});
      }

      if (fuel < c) {
        int new_fuel = fuel + 1;
        int new_dist = dist + price[u];
        dp[u][new_fuel] = min(dp[u][new_fuel], new_dist);
        pq.push({new_dist, u, new_fuel});
      }
    }

    if (result != -1) {
      cout << result << "\n";
    } else {
      cout << "impossible" << "\n";
    }
  }
}
