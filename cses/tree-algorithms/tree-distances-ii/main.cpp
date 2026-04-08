#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAXN = 2e5 + 1;
int n;
vector<int> adj[MAXN];
ll subtree_size[MAXN];
ll dist_sum[MAXN];

void dfs(int u, int p, ll depth) {
  subtree_size[u] = 1;
  dist_sum[1] += depth;
  for (int v : adj[u]) {
    if (v != p) {
      dfs(v, u, depth + 1);
      subtree_size[u] += subtree_size[v];
    }
  }
}

void dfs2(int u, int p) {
  for (int v : adj[u]) {
    if (v != p) {
      dist_sum[v] = dist_sum[u] - subtree_size[v] + (n - subtree_size[v]);
      dfs2(v, u);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1, 0, 0);
  dfs2(1, 0);

  for (int i = 1; i <= n; ++i) {
    cout << dist_sum[i] << " ";
  }
  cout << "\n";
}
