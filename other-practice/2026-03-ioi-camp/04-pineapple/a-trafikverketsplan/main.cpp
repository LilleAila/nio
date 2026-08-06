#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

vector<vector<int>> parent;
vector<int> height;
vector<vector<int>> adj_undirected;
vector<vector<int>> adj;
vector<vector<int>> adj_rev;

void dfs(int u, int p, int depth) {
  height[u] = depth;
  for (int v : adj_undirected[u]) {
    if (v != p) dfs(v, u, depth+1);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  height.resize(n);
  adj_undirected.resize(n);
  // adj.resize(n);
  // adj_rev.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    // to 0-indexed
    --a;
    --b;
    adj_undirected[a].push_back(b);
    adj_undirected[b].push_back(a);
    // adj[a].push_back(b);
    // adj_rev[b].push_back(a);
  }

  dfs(0, -1, 0);

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int h, w;
    cin >> h >> w;
    // to 0-indexed
    --h;
    --w;
  }
}
