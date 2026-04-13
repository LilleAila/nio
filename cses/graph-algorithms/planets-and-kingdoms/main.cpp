#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> adj[N];
vector<int> adj_rev[N];
bool visited[N];

stack<int> s;

void dfs1(int u) {
  visited[u] = true;
  for (int v : adj[u])
    if (!visited[v])
      dfs1(v);
  s.push(u);
}

int component[N];

void dfs2(int u, int id) {
  visited[u] = true;
  component[u] = id;
  for (int v : adj_rev[u])
    if (!visited[v])
      dfs2(v, id);
  s.push(u);
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
    adj_rev[b].push_back(a);
  }

  for (int i = 1; i <= n; ++i)
    if (!visited[i])
      dfs1(i);

  fill(visited, visited + n + 1, false);

  int component_id = 0;
  while (!s.empty()) {
    int u = s.top();
    s.pop();
    if (!visited[u])
      dfs2(u, ++component_id);
  }

  cout << component_id << "\n";
  for (int i = 1; i <= n; ++i)
    cout << component[i] << " ";
  cout << "\n";
}
