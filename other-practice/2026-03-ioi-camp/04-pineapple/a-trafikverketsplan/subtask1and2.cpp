// Wi = 1 for all i

#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

vector<vector<int>> adj_rev;
vector<vector<int>> adj;
vector<bool> visited;

// Dfs to check whether a path exists from u to target
bool dfs1(int u, int target) {
  if (u == target) return true;
  bool result = false;
  for (int v : adj[u]) {
    if (dfs1(v, target)) result = true;;
  }
  return result;
}

// Dfs to find all nodes reachable from u
void dfs2(int u) {
  visited[u] = true;
  for (int v : adj_rev[u]) {
    dfs2(v);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  adj_rev.resize(n);
  adj.resize(n);
  visited.assign(n, false);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    // to 0-indexed
    --a;
    --b;
    adj_rev[b].push_back(a);
    adj[a].push_back(b);
  }

  dfs2(0);

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int h, w;
    cin >> h >> w;
    // to 0-indexed
    --h;
    --w;
    if (n <= 1000) {
      cout << (dfs1(h, w) ? "ja" : "nej") << "\n";
    } else {
      cout << (visited[h] ? "ja" : "nej") << "\n";
    }
  }
}
