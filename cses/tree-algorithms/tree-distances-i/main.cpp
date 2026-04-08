#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  queue<int> q;

  vector<int> dist(n + 1, INT_MAX);
  dist[1] = 0;
  q.push(1);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      int d = dist[u] + 1;
      if (d < dist[v]) {
        dist[v] = d;
        q.push(v);
      }
    }
  }

  int node = 1;
  int max_dist = 0;
  for (int i = 2; i <= n; ++i) {
    if (dist[i] > max_dist) {
      node = i;
      max_dist = dist[i];
    }
  }

  vector<int> dist2(n + 1, INT_MAX);
  dist2[node] = 0;
  q.push(node);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      int d = dist2[u] + 1;
      if (d < dist2[v]) {
        dist2[v] = d;
        q.push(v);
      }
    }
  }

  int node2 = 1;
  int max_dist2 = 0;
  for (int i = 1; i <= n; ++i) {
    if (dist2[i] > max_dist2) {
      node2 = i;
      max_dist2 = dist2[i];
    }
  }

  vector<int> dist3(n + 1, INT_MAX);
  dist3[node2] = 0;
  q.push(node2);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      int d = dist3[u] + 1;
      if (d < dist3[v]) {
        dist3[v] = d;
        q.push(v);
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << max(dist2[i], dist3[i]) << " ";
  }
  cout << "\n";
}
