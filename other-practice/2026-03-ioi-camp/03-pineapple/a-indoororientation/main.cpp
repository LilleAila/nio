#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const int N_STAIRS = 26;
const ll INF = LLONG_MAX / 3;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  // stairwell[n] = vector<{node height, node id}>
  vector<vector<pair<int, int>>> stairwells(N_STAIRS);

  for (int i = 0; i < n; ++i) {
    int f;
    string stairs;
    cin >> f >> stairs;
    for (char s : stairs) {
      int stair = s - 'A';
      stairwells[stair].push_back({f, i});
    }
  }

  // {cost, node id}
  vector<vector<pair<int, int>>> graph(n);
  for (auto &s : stairwells) {
    sort(s.begin(), s.end());

    if (s.size() > 1) {
      for (size_t i = 0; i+1 < s.size(); ++i) {
        auto [hu, u] = s[i];
        auto [hv, v] = s[i+1];
        int dh = abs(hv - hu);

        graph[u].push_back({dh, v});
        graph[v].push_back({dh, u});
      }
    }
  }

  ll result = 0;
  for (int target = 1; target < n; ++target) {
    int start = target - 1;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    vector<ll> dist(n, INF);
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();

      if (d > dist[u]) continue;
      if (u == target) break;

      for (auto &[c, v] : graph[u]) {
        int new_dist = d + c;
        if (new_dist < dist[v]) {
          dist[v] = new_dist;
          pq.push({dist[v], v});
        }
      }
    }

    result += dist[target];
  }

  cout << result << "\n";
}
