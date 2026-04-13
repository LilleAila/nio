#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;
const ll INF = LLONG_MAX;
const int N = 1e5 + 1;

vector<pair<int, ll>> graph[N];
ll dist[N];

ll path_count[N];
ll min_flights[N];
ll max_flights[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  while (m--) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
  }

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  fill(dist, dist + n + 1, INF);
  dist[1] = 0;
  path_count[1] = 1;
  fill(min_flights, min_flights + n + 1, INF);
  min_flights[1] = 0;
  max_flights[1] = 0;

  pq.push({0, 1});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u])
      continue;

    for (auto [v, c] : graph[u]) {
      ll new_dist = d + c;
      if (new_dist < dist[v]) {
        dist[v] = new_dist;
        path_count[v] = path_count[u];
        min_flights[v] = min_flights[u] + 1;
        max_flights[v] = max_flights[u] + 1;
        pq.push({new_dist, v});
      } else if (new_dist == dist[v]) {
        path_count[v] = (path_count[u] + path_count[v]) % MOD;
        min_flights[v] = min(min_flights[v], min_flights[u] + 1);
        max_flights[v] = max(max_flights[v], max_flights[u] + 1);
      }
    }
  }

  cout << dist[n] << " " << path_count[n] << " " << min_flights[n] << " "
       << max_flights[n] << "\n";
}
