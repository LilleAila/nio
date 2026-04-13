#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
int in_degree[N];
vector<int> result;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    ++in_degree[b];
  }

  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);

    for (int v : adj[u]) {
      --in_degree[v];
      if (in_degree[v] == 0) {
        q.push(v);
      }
    }
  }

  if (result.size() != (size_t)n) {
    cout << "IMPOSSIBLE" << "\n";
  } else {
    for (int x : result)
      cout << x << " ";
    cout << "\n";
  }
}
