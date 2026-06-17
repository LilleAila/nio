#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 3e5 + 1;
vector<int> adj[MAXN];
// We already know this is a DAG
// thus, int visited is unnecessary
bool visited[MAXN];

bool dfs(int u, int t) {
  if (u == t) return true;

  visited[u] = true;
  for (int v : adj[u]) {
    if (!visited[v]) {
      if (dfs(v, t)) {
        return true;
      };
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  int q;
  cin >> q;

  while (q--) {
    fill (visited, visited + MAXN, false);

    int h, w;
    cin >> h >> w;
    if (dfs(h, w)) {
      cout << "ja" << "\n";
    } else {
      cout << "nej" << "\n";
    }
  }
}
