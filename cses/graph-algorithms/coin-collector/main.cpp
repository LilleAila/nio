#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1e5 + 1;
vector<int> adj[N];
vector<int> adj_rev[N];
bool visited[N];
ll coins[N];
stack<int> s;

int scc[N];
ll scc_coins[N];

void dfs1(int u) {
  visited[u] = true;
  for (int v : adj[u])
    if (!visited[v])
      dfs1(v);
  s.push(u);
}

void dfs2(int u, int id) {
  visited[u] = true;
  scc[u] = id;
  scc_coins[id] += coins[u];
  for (int v : adj_rev[u])
    if (!visited[v])
      dfs2(v, id);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    cin >> coins[i];
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj_rev[b].push_back(a);
  }

  for (int i = 1; i <= n; ++i)
    if (!visited[i])
      dfs1(i);
  fill(visited, visited + n + 1, false);

  int scc_id = 0;
  while (!s.empty()) {
    int u = s.top();
    s.pop();

    if (!visited[u])
      dfs2(u, ++scc_id);
  }

  vector<int> in_degree(scc_id + 1, 0);
  vector<vector<int>> cond_adj(scc_id + 1);
  for (int u = 1; u <= n; ++u) {
    for (int v : adj[u]) {
      if (scc[u] != scc[v]) {
        cond_adj[scc[u]].push_back(scc[v]);
      }
    }
  }

  for (int i = 1; i <= scc_id; ++i) {
    sort(cond_adj[i].begin(), cond_adj[i].end());
    cond_adj[i].erase(unique(cond_adj[i].begin(), cond_adj[i].end()),
                      cond_adj[i].end());
    for (int v : cond_adj[i]) {
      in_degree[v]++;
    }
  }

  queue<int> q;
  vector<ll> dp(scc_id + 1, 0);
  for (int i = 1; i <= scc_id; ++i) {
    if (in_degree[i] == 0)
      q.push(i);
    dp[i] = scc_coins[i];
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : cond_adj[u]) {
      ll new_coins = dp[u] + scc_coins[v];
      if (new_coins > dp[v])
        dp[v] = new_coins;

      --in_degree[v];
      if (in_degree[v] == 0)
        q.push(v);
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << "\n";
}
