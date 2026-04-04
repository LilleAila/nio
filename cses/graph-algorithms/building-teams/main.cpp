#include <iostream>
#include <numeric>
#include <queue>
#include <unordered_set>
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

  // 0: unassigned (not visited)
  // 1: team 1
  // 2: team 2
  vector<int> team(n + 1, 0);
  queue<int> q;

  // Find cycles and assign alternating teams
  for (int i = 1; i <= n; ++i) {
    if (!team[i]) {
      team[i] = 1;
      q.push(i);
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int v : adj[u]) {
        if (!team[v]) {
          if (team[u] == 1)
            team[v] = 2;
          else
            team[v] = 1;
          q.push(v);
        } else if (team[v] == team[u]) {
          cout << "IMPOSSIBLE" << endl;
          return 0;
        }
      }
    }
  }

  for (int i = 1; i <= n; i++)
    cout << team[i] << " ";
  cout << endl;
}
