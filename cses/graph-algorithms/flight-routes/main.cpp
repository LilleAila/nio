#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX;
const int MAXN = 1e5 + 5;
vector<pair<int, ll>> graph[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t n, m, k;
  cin >> n >> m >> k;

  while (m--) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
  }

  // (dist, node)
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;
  priority_queue<ll> dists[MAXN];
  size_t extracted[MAXN] = {0};

  dists[1].push(0);
  pq.push({0, 1});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    extracted[u]++;
    if (extracted[u] > k)
      continue;

    for (const auto &[v, c] : graph[u]) {
      ll new_dist = d + c;
      if (dists[v].size() < k) {
        dists[v].push(new_dist);
        pq.push({new_dist, v});
      } else if (new_dist < dists[v].top()) {
        dists[v].pop();
        dists[v].push(new_dist);
        pq.push({new_dist, v});
      }
    }
  }

  vector<ll> result;
  while (!dists[n].empty()) {
    result.push_back(dists[n].top());
    dists[n].pop();
  }
  reverse(result.begin(), result.end());
  for (ll i : result)
    cout << i << " ";
  cout << "\n";
}
