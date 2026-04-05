#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 7;
vector<int> adj[MAXN];
int subordinates[MAXN];

int dfs(int u) {
  int ss = 1;
  for (int v : adj[u]) {
    ss += dfs(v);
  }
  subordinates[u] = ss - 1;
  return ss;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 2; i <= n; ++i) {
    int p;
    cin >> p;
    adj[p].push_back(i);
  }

  dfs(1);

  for (int i = 1; i <= n; ++i) {
    cout << subordinates[i] << " ";
  }
  cout << endl;
}
