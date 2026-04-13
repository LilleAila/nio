// Using 2 dfs-passes (basically simplified kosaraju)

#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
vector<int> adj1[N];
vector<int> adj2[N];

bool visited[N];

void dfs(int u, vector<int> graph[]) {
  visited[u] = true;
  for (int v : graph[u]) {
    if (!visited[v])
      dfs(v, graph);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj1[a].push_back(b);
    adj2[b].push_back(a);
  }

  dfs(1, adj1);
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      cout << "NO\n1 " << i << "\n";
      return 0;
    }
  }
  fill(visited, visited + n + 1, false);
  dfs(1, adj2);
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      cout << "NO\n" << i << " 1\n";
      return 0;
    }
  }

  cout << "YES" << endl;
}
