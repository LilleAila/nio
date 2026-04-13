// Using full kosaraju

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> adj[N];
vector<int> rev_adj[N];
stack<int> s;

bool visited[N];

void dfs1(int u) {
  visited[u] = true;
  for (int v : adj[u])
    if (!visited[v])
      dfs1(v);
  s.push(u);
}

void dfs2(int u) {
  visited[u] = true;
  for (int v : rev_adj[u])
    if (!visited[v])
      dfs2(v);
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
    rev_adj[b].push_back(a);
  }

  for (int i = 1; i <= n; ++i)
    if (!visited[i])
      dfs1(i);

  fill(visited, visited + n + 1, false);
  vector<int> roots;
  while (!s.empty()) {
    int u = s.top();
    s.pop();
    if (!visited[u]) {
      roots.push_back(u);
      dfs2(u);
    }
  }

  if (roots.size() == 1) {
    cout << "YES" << "\n";
  } else {
    cout << "NO\n" << roots[1] << " " << roots[0] << "\n";
  }
}
