// Wi = 1 for all i

#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

vector<vector<int>> adj_rev;
vector<bool> visited;

void dfs(int u) {
  visited[u] = true;
  for (int v : adj_rev[u]) {
    dfs(v);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  adj_rev.resize(n);
  visited.assign(n, false);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    // to 0-indexed
    --a;
    --b;
    adj_rev[b].push_back(a);
  }

  dfs(0);

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int h, w;
    cin >> h >> w;
    // to 0-indexed
    --h;
    --w;
    cout << (visited[h] ? "ja" : "nej") << "\n";
  }
}
