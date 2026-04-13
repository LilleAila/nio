#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
const int NODES = N * 2;

vector<int> adj[NODES];
vector<int> adj_rev[NODES];

bool visited[NODES];
stack<int> s;
int component[NODES];

void dfs1(int u) {
  visited[u] = true;
  for (int v : adj[u])
    if (!visited[v])
      dfs1(v);
  s.push(u);
}

void dfs2(int u, int component_id) {
  visited[u] = true;
  component[u] = component_id;
  for (int v : adj_rev[u])
    if (!visited[v])
      dfs2(v, component_id);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int a, b;
    char x, y;
    cin >> x >> a >> y >> b;
    bool wants_a = x == '+';
    bool wants_b = y == '+';

    int node_a = wants_a ? a << 1 | 1 : a << 1;
    int node_b = wants_b ? b << 1 | 1 : b << 1;

    adj[node_a ^ 1].push_back(node_b);
    adj_rev[node_b].push_back(node_a ^ 1);
    adj[node_b ^ 1].push_back(node_a);
    adj_rev[node_a].push_back(node_b ^ 1);
  }

  for (int i = 1; i <= m * 2; ++i)
    if (!visited[i])
      dfs1(i);
  fill(visited, visited + m * 2 + 2, false);

  int component_id = 0;
  while (!s.empty()) {
    int u = s.top();
    s.pop();

    if (!visited[u]) {
      dfs2(u, ++component_id);
    }
  }

  vector<bool> result(m + 1);
  for (int i = 1; i <= m; ++i) {
    if (component[i << 1] == component[i << 1 | 1]) {
      cout << "IMPOSSIBLE" << endl;
      return 0;
    }

    if (component[i << 1 | 1] > component[i << 1])
      result[i] = true;
    else
      result[i] = false;
  }

  for (int i = 1; i <= m; ++i)
    cout << (result[i] ? "+ " : "- ");
  cout << "\n";
}
