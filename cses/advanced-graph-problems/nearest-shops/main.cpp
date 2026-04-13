#include <array>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> shops(k);
  vector<bool> shop(n + 1, false);
  for (int i = 0; i < k; ++i) {
    cin >> shops[i];
    shop[shops[i]] = true;
  }

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<array<pair<ll, int>, 2>> dist(
      n + 1, array<pair<ll, int>, 2>{{{INF, -1}, {INF, -1}}});
  queue<pair<int, int>> q;

  for (int s : shops) {
    dist[s][0] = {0, s};
    q.push({s, s});
  }

  while (!q.empty()) {
    auto [u, src] = q.front();
    q.pop();

    ll dist_u =
        (dist[u][0].second == src) ? dist[u][0].first : dist[u][1].first;

    for (int v : adj[u]) {
      ll new_dist = dist_u + 1;

      if (new_dist < dist[v][0].first) {
        if (dist[v][0].second != src) {
          dist[v][1] = dist[v][0];
        }
        dist[v][0] = {new_dist, src};
        q.push({v, src});
      } else if (new_dist < dist[v][1].first && src != dist[v][0].second) {
        dist[v][1] = {new_dist, src};
        q.push({v, src});
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    ll result = INF;

    if (shop[i]) {
      result = dist[i][1].first;
    } else {
      result = dist[i][0].first;
    }

    if (result >= INF)
      cout << -1 << " ";
    else
      cout << result << " ";
  }
  cout << "\n";
}
