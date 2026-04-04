#include <iostream>
#include <stack>
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

  vector<int> visited(n + 1, 0);
  vector<int> parent(n + 1, 0);

  for (int i = 0; i <= n; ++i) {
    if (visited[i] == 0) {
      stack<int> s;
      s.push(i);

      while (!s.empty()) {
        int u = s.top();

        if (visited[u] == 0) {
          // 1: "in-progress" - will be revisited after children are done being
          // visited and we potentially find a cycle.
          visited[u] = 1;
        } else {
          visited[u] = 2;
          s.pop();
          continue;
        }

        for (int v : adj[u]) {
          if (v == parent[u])
            continue;

          if (visited[v] == 1) {
            // Found an "in-progress" node => found a cycle
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
            parent[v] = u;
            s.push(v);
          }
        }
      }
    }
  }

  // No cycle was found
  cout << "IMPOSSIBLE" << endl;
}
