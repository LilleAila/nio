#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

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

  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      pq;
  vector<long long> dist(n + 1, LLONG_MAX);
  dist[1] = 0;
  pq.push({0, 1});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u])
      continue;

    for (const auto &[v, weight] : graph[u]) {
      long long new_dist = d + weight;
      if (new_dist < dist[v]) {
        dist[v] = new_dist;
        pq.push({new_dist, v});
      }
    }
  }

  for (int i = 1; i <= n; ++i)
    cout << dist[i] << " ";
  cout << "\n";
}
