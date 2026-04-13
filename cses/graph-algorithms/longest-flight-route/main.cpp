#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
int dist[N];
int in_degree[N];
int parent[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    in_degree[b]++;
  }

  fill(dist, dist + N, -1e9);
  dist[1] = 1;

  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (in_degree[i] == 0)
      q.push(i);
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      if (dist[u] != -1e9 && dist[u] + 1 > dist[v]) {
        dist[v] = dist[u] + 1;
        parent[v] = u;
      }
      in_degree[v]--;
      if (in_degree[v] == 0)
        q.push(v);
    }
  }

  if (dist[n] < 0) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << dist[n] << endl;
    vector<int> path;
    for (int i = n; i != 0; i = parent[i])
      path.push_back(i);
    reverse(path.begin(), path.end());
    for (int i : path)
      cout << i << " ";
    cout << "\n";
  }
}
