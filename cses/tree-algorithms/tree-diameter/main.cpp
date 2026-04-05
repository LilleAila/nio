#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 1;
vector<int> adj[MAXN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  queue<int> q;
  vector<int> dist(n + 1, INT_MAX);
  q.push(1);
  dist[1] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      int new_dist = dist[u] + 1;
      if (new_dist < dist[v]) {
        dist[v] = new_dist;
        q.push(v);
      }
    }
  }

  int node = 1;
  int max_dist = 0;
  for (int i = 1; i <= n; ++i) {
    if (dist[i] > max_dist) {
      max_dist = dist[i];
      node = i;
    }
  }

  dist.assign(n + 1, INT_MAX);
  q.push(node);
  dist[node] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      int new_dist = dist[u] + 1;
      if (new_dist < dist[v]) {
        dist[v] = new_dist;
        q.push(v);
      }
    }
  }

  cout << *max_element(dist.begin() + 1, dist.end()) << endl;
}
