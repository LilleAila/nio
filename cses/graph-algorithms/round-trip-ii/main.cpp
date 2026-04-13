#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
int state[N];
int parent[N];

int cycle_start = -1;
int cycle_end = -1;

bool dfs(int u) {
  state[u] = 1;

  for (int v : adj[u]) {
    if (state[v] == 0) {
      parent[v] = u;
      if (dfs(v))
        return true;
    } else if (state[v] == 1) {
      cycle_end = u;
      cycle_start = v;
      return true;
    }
  }

  state[u] = 2;
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; ++i) {
    if (state[i] == 0 && dfs(i))
      break;
  }

  if (cycle_start == -1) {
    cout << "IMPOSSIBLE" << "\n";
  } else {
    vector<int> cycle;
    cycle.push_back(cycle_start);
    for (int i = cycle_end; i != cycle_start; i = parent[i])
      cycle.push_back(i);
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << "\n";
    for (int x : cycle)
      cout << x << " ";
    cout << "\n";
  }
}
