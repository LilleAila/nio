#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
bool visited[MAXN];
bool matched[MAXN];

int dfs(int u) {
  int matchings = 0;

  for (int v : adj[u]) {
    if (!visited[v]) {
      visited[v] = true;
      matchings += dfs(v);

      if (!matched[v] && !matched[u]) {
        matched[v] = true;
        matched[u] = true;
        matchings++;
      }
    }
  }

  return matchings;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int result = dfs(1);
  cout << result << endl;
}
