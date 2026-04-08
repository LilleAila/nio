#include <climits>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

const long long INF = LLONG_MIN / 2;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, long long>> edges(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    long long x;
    cin >> a >> b >> x;
    edges[i] = {a, b, x};
  }

  vector<long long> dist(n + 1, INF);
  dist[1] = 0;
  for (int i = 0; i < n - 1; ++i) {
    for (const auto &[u, v, x] : edges) {
      if (dist[u] != INF && dist[u] + x > dist[v]) {
        dist[v] = dist[u] + x;
      }
    }
  }

  long long result = dist[n];

  vector<bool> cycle(n + 1, false);
  for (int i = 0; i <= n; ++i) {
    for (const auto &[u, v, x] : edges) {
      if (dist[u] != INF && dist[u] + x > dist[v]) {
        dist[v] = dist[u] + x;
        cycle[v] = true;
      }
      if (cycle[u])
        cycle[v] = true;
    }
  }

  if (cycle[n]) {
    cout << -1 << endl;
  } else {
    cout << result << endl;
  }
}
