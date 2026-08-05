#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

vector<vector<int>> adj;
vector<int> parent;
vector<int> height;
vector<vector<int>> dest;

// Root the tree and find the heights
void dfs(int u, int depth) {
  height[u] = depth;
  for (int v : adj[u]) {
    if (v != parent[u]) {
      parent[v] = u;
      dfs(v, depth + 1);
    }
  }
}

int lca(int u, int v) {
  // Ensure u is further down the tree than h (greater height)
  // Then, lift u by powers of 2 until the heights are equal
  if (height[u] < height[v]) swap(u, v);
  int height_diff = height[u] - height[v];
  for (int i = 0; i < K; ++i) {
    if (height_diff & (1 << i)) {
      u = dest[i][u];
    }
  }

  if (u == v) return u;

  // Loop to replicate the functionality of bit_ceil from c++20
  // Find the lowest value of k such that 2^k is >= beight[u]
  // This should return the minimum k which resolves to the root node
  // int k = -1;
  // for (int i = 0; i < K; ++i) {
  //   if (1 << i >= height[u]) {
  //     k = i;
  //     break;
  //   }
  // }

  for (int i = K - 1; i >= 0; --i) {
    if (dest[i][u] != dest[i][v]) {
      u = dest[i][u];
      v = dest[i][v];
    }
  }

  return dest[0][u];
}

int main() {
  ios::sync_with_stdio(false),
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n, q;
  cin >> n >> q;

  // Read input as an undirected graph
  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  height.resize(n);
  parent.resize(n);
  parent[0] = 0;
  dfs(0, 0);

  // Initialize destination vector
  dest.assign(K, vector<int>(n));
  dest[0] = parent;
  for (int k = 1; k < K; ++k) {
    for (int i = 0; i < n; ++i) {
      dest[k][i] = dest[k-1][dest[k-1][i]];
    }
  }

  while (q--) {
    int u, v;
    cin >> u >> v;
    --u;
    --v;
    int p = lca(u, v);
    int result = height[u] + height[v] - 2 * height[p];
    cout << result << "\n";
  }
}
