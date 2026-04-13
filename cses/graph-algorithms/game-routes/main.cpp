#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;
const int N = 1e5 + 5;
vector<int> adj[N];
int in_degree[N];
ll paths[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    ++in_degree[b];
  }

  queue<int> q;

  for (int i = 1; i <= n; ++i) {
    if (in_degree[i] == 0)
      q.push(i);
  }

  paths[1] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      paths[v] = (paths[v] + paths[u]) % MOD;

      --in_degree[v];
      if (in_degree[v] == 0) {
        q.push(v);
      }
    }
  }

  cout << paths[n] << endl;
}
