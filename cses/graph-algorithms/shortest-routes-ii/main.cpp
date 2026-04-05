#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

const long long INF = LLONG_MAX / 2;
const int MAXN = 501;
vector<pair<int, int>> graph[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

  for (int i = 1; i <= n; ++i) {
    dist[i][i] = 0;
  }

  while (m--) {
    int a, b;
    long long c;
    cin >> a >> b >> c;
    dist[a][b] = min(dist[a][b], c);
    dist[b][a] = min(dist[b][a], c);
  }

  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    if (dist[a][b] != INF) {
      cout << dist[a][b] << "\n";
    } else {
      cout << "-1" << "\n";
    }
  }
}
