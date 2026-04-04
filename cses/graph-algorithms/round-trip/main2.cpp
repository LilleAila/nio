#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<bool> visited(n + 1, false);
  vector<int> parent(n + 1, 0);

  for (int i = 0; i <= n; ++i) {
    if (visited[i] == 0) {
      stack<pair<int, int>> s;
      s.push({i, 0});

      while (!s.empty()) {
        auto [u, p] = s.top();
        s.pop();

        visited[u] = true;
        parent[u] = p;

        for (int v : adj[u]) {
          if (v == p)
            continue;

          if (visited[v]) {
            vector<int> cycle;
            cycle.push_back(v);
            for (int j = u; j != v; j = parent[j]) {
              cycle.push_back(j);
            }
            cycle.push_back(v);
            cout << cycle.size() << endl;
            for (int n : cycle)
              cout << n << " ";
            cout << endl;
            return 0;
          }

          if (visited[v] == 0) {
            s.push({v, u});
          }
        }
      }
    }
  }

  // No cycle was found
  cout << "IMPOSSIBLE" << endl;
}
