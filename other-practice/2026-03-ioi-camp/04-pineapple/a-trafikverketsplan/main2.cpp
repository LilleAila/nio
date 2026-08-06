#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

vector<vector<tuple<int, int>>> adj;
vector<int> height;
vector<int> parent;
vector<vector<int>> dest;
vector<int> path_weight;

void dfs(int u, int depth) {
  height[u] = depth;
  for (const auto &[v, w] : adj[u]) {
    if (v == parent[u]) continue;
    parent[v] = u;
    path_weight[v] = path_weight[u] + w;
    dfs(v, depth+1);
  }
}

int lca(int u, int v) {
  if (height[u] < height[v]) swap(u, v);
  int dh = height[u] - height[v];
  for (int i = 0; i < K; ++i) if (dh & (1 << i)) u = dest[i][u];

  if (u == v) return u;

  for (int i = K-1; i >= 0; --i) {
    if (dest[i][u] != dest[i][v]) {
      u = dest[i][u];
      v = dest[i][v];
    }
  }

  return dest[0][u];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  adj.resize(n);
  for (int i = 0; i < n-1; ++i) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    adj[a].push_back({b, 1});
    adj[b].push_back({a, -1});
  }

  parent.assign(n, 0);
  height.assign(n, 0);
  path_weight.assign(n, 0);
  dfs(0, 0);

  // cerr << path_weight[0] << "\n";
  // cerr << path_weight[1] << "\n";
  // cerr << path_weight[4] << "\n";

  dest.assign(K, vector<int>(n));
  dest[0] = parent;
  for (int k = 1; k < K; ++k) {
    for (int i = 0; i < n; ++i) {
      dest[k][i] = dest[k-1][dest[k-1][i]];
    }
  }

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    // cerr << "\n";
    int h, w;
    cin >> h >> w;
    --h;
    --w;

    int lca_node = lca(h, w);

    // cerr << h << " " << w << "\n";
    // cerr << path_weight_rev[h] << " " << path_weight_rev[lca_node] << " " << (path_weight_rev[h] - path_weight_rev[lca_node]) << "\n";

    int dist = height[h] + height[w] - 2 * height[lca_node];
    int weight = -(path_weight[h] - path_weight[lca_node]) + (path_weight[w] - path_weight[lca_node]);

    // cerr << dist << " " << weight << "\n";

    if (dist == weight) cout << "ja" << "\n";
    else cout << "nej" << "\n";
  }
}
