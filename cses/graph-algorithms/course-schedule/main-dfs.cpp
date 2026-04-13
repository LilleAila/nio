#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];
int state[N];
vector<int> result;

bool dfs(int u) {
  state[u] = 1;

  for (int v : adj[u]) {
    if (state[v] == 1)
      return false; // Cycle

    if (state[v] == 0) {
      if (!dfs(v))
        return false; // Also cycle
    }
  }

  state[u] = 2;
  result.push_back(u);
  return true;
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
    if (state[i] == 0) {
      if (!dfs(i)) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
      }
    }
  }

  reverse(result.begin(), result.end());
  for (int x : result)
    cout << x << " ";
  cout << "\n";
}
